const quantity_regex = new RegExp("^[0-9]{0,3}$");
const preceding_zeros_regex = new RegExp("0{1,3}([1-9]{1,3})");
const quantity_element = document.getElementById('quantity');

var before_quantity_val = "0";

document.addEventListener('DOMContentLoaded', function () {
	//only allow letters in the text box
	quantity_element.addEventListener("beforeinput", (event) => {
		if(event.data != null && !quantity_regex.test(event.data)){
			event.preventDefault();
		}
	});

	//only allow values 0-999 in the text box
	quantity_element.addEventListener("input", (event) => {
		if(!quantity_regex.test(event.target.value)){
			quantity_element.value = before_quantity_val;
		}
		if(quantity_element.value == ""){
			quantity_element.value = "0";
		}
		quantity_element.value = quantity_element.value.replace(preceding_zeros_regex, "$1");
		before_quantity_val = quantity_element.value;
	});
	
	document.getElementById('number_less_btn').addEventListener('click', async () => {
		if(quantity_element.value > 0)
		{
			quantity_element.value--;
		}
	});
	
	document.getElementById('number_more_btn').addEventListener('click', async () => {
		if(quantity_element.value < 999)
		{
			quantity_element.value++;
		}
	});

    document.getElementById('save_btn').addEventListener('click', async () => {
		var num = parseInt(quantity_element.value);
		var filename = "";
		if(isNaN(num)){
			return null;
		}
		if(num < 10){
			filename = "puzzle_00" + num.toString() + ".txt";
		}else if(num < 100){
			filename = "puzzle_0" + num.toString() + ".txt";
		}else{
			filename = "puzzle_" + num.toString() + ".txt";
		}
		var tab = await getCurTab();
		if(typeof tab != "undefined"){
			chrome.scripting.executeScript({
				target : {tabId : tab.id, allFrames : true},
				func : readPgn,
			}).then(injectionResults => {
				for (const {frameId, result} of injectionResults) {
					if(result == "" || result == null){
						continue;
					}
					var element = document.createElement('a');
					element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(result));
					element.setAttribute('download', filename);
					element.style.display = 'none';
					document.body.appendChild(element);
					element.click();
					document.body.removeChild(element);
					chrome.storage.local.set({puzz_num: num + 1}).then();
					quantity_element.value = num + 1;
				}
			});
		}
	});
});

const data = await chrome.storage.local.get(["puzz_num"]);
if(typeof data.puzz_num == "number"){
	quantity_element.value = data.puzz_num;
	before_quantity_val = data.puzz_num;
}

async function getCurTab()
{
	let queryOptions = { active: true, lastFocusedWindow: true, url: ["https://lichess.org/*"] };
	let [tab] = await chrome.tabs.query(queryOptions);
	return tab;
}

function readPgn(){
	ch = document.querySelector("div.tview2.tview2-column").children;
	pgn = "";
	start_i = 0;
	end_i = 0;
	start_c = "w";
	moves_i = 0;
	for(let i = 0; i < ch.length; i++){
		if(ch[i].tagName == 'MOVE' && ch[i].className != 'empty'){
			pgn = pgn + " " + ch[i].innerText.split("\n")[0];
			moves_i += 1;
			
			if(ch[i].className == 'current' || ch[i].className == 'current active'|| ch[i].className == 'active current'){
				start_i = Math.ceil((moves_i + 1) / 2);
				if(moves_i % 2 == 1){
					start_c = "b";
				}
			}
			if(ch[i].className == 'win' || ch[i].className == 'win active' || ch[i].className == 'active win'){
				end_i = Math.ceil(moves_i / 2);
				break;
			}
			if(ch[i].className == 'good' || ch[i].className == 'good active'|| ch[i].className == 'good current'){
				end_i = Math.ceil(moves_i / 2);
			}
		}
	}
	if(pgn == "" || end_i < start_i){
		return null;
	}
	return start_i.toString() + start_c + "\n" + end_i.toString() + start_c + "\n" + pgn;
}
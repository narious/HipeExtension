
async function init() {
    var now;
    var big_digits = document.getElementById('big_digits');
    var small_digits = document.getElementById('small_digits');
    while(true) {
        now = new Date();
        big_digits.innerText =`0${now.getHours()}`.slice(-2) + ':' + `0${now.getMinutes()}`.slice(-2);
        small_digits.innerText = ':'  + `0${now.getSeconds()}`.slice(-2);
        await new Promise(r => setTimeout(r, 1000)); 
    }
}

init();
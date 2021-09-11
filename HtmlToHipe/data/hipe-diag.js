
function showDialog (){
    var dialogBox = document.getElementById('dialogBox');
    if (typeof dialogBox.showModal === "function") {
        dialogBox.showModal();
    } else {
        alert("The <dialog> API is not supported by this browser");
    }
}

function showSimpleDialog (){
    var dialogBox = document.getElementById('dialogSimple');
    if (typeof dialogBox.showModal === "function") {
        dialogBox.showModal();
    } else {
        alert("The <dialog> API is not supported by this browser");
    }
}

function showTextDialog(){}

function showFifoOpen(){
    document.getElementById('fileInput').click();
}


function init() {
    var dialogButton = document.getElementById("dialogButton");
    var dialog2Button = document.getElementById("dialog2Button");
    var textDialogButton = document.getElementById("textDialogButton");
    var fifoOpenButton = document.getElementById("fifoOpenButton");

    dialogButton.addEventListener('click', showDialog);
    dialog2Button.addEventListener('click', showSimpleDialog);
    textDialogButton.addEventListener('click', showTextDialog);
    fifoOpenButton.addEventListener('click', showFifoOpen);

    var selectEl = document.getElementById('select1');
    var confirmBtn = document.getElementById('confirmBtn');

    selectEl.addEventListener('change', () => confirmBtn.value = selectEl.value);

}  

init();
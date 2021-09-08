
// Sets the parameters for the canvas

var canvas, ctx, flag = false, // flag is true after a mouse down event (enforcing a draw only after a mouse down)
    prevX = 0,
    currX = 0,
    prevY = 0,
    currY = 0;

var stroke_style = 'black', line_width = 2;
function init() {
    canvas = document.getElementById('canv');
    ctx = canvas.getContext('2d');
    w = canvas.width;
    h = canvas.height;

    ctx.font = "30px Arial";
    ctx.strokeText("Draw!", 10, 50);

    canvas.addEventListener('mousemove', e => {handle_event('move', e)}, false);
    canvas.addEventListener('mousedown', e => {handle_event('down', e)}, false);
    canvas.addEventListener('mouseup', e => {handle_event('up', e)}, false);
    canvas.addEventListener('mouseout', e => {handle_event('out', e)}, false);
    const updateXY = (e) => {
        prevY = currY;
        prevX = currX;
        currY = e.clientY - canvas.getBoundingClientRect().top;
        currX = e.clientX - canvas.getBoundingClientRect().left;
        // currY = e.clientY
        // currX = e.clientX
    }

    function handle_event(res, e) {
        if (res == 'down') {
            updateXY(e);
            flag = true;
            draw_dot();
            return;
        }

        flag = res == 'up' || res == 'out' ? false : flag;

        if (res == 'move' && flag == true) {
            updateXY(e);
            draw();
            return;
        }
        
    }

    const color = (obj) => stroke_style = obj.id;

    const draw_dot = () => {
        ctx.beginPath();
        ctx.fillStyle = stroke_style;
        ctx.fillRect(currX, currY, 2, 2);
        ctx.closePath();
    }
    const draw = () => {
        ctx.beginPath();

        ctx.moveTo(prevX, prevY);
        ctx.lineTo(currX, currY);
        ctx.strokeStyle = stroke_style;
        ctx.lineWidth = line_width;
        ctx.stroke();
        ctx.closePath();
    }

    function erase() {}

    function save() {}

}

init();
var i = 0;

var bg = new Image();
bg.src = "bg.png";
var sprite = new Image();
sprite.src = "batman.png";

function init() {
    setInterval(draw, 1000);
}

function clear(ctx) {
//    ctx.clearRect(0, 0, 320, 200);
//    ctx.globalCompositeOperation = 'source-over';
    ctx.drawImage(bg, 0, 0);
}

function drawBatman(ctx) {
    ctx.save();
    ctx.translate(160, 100);
    ctx.rotate(i);
    ctx.drawImage(sprite, 0, 0, 90, 30);
    ctx.restore();
}

function draw() {
    var canvas = document.getElementById('example');
    var ctx = canvas.getContext('2d');
    clear(ctx);
//    ctx.globalCompositeOperation = 'lighter';
    
    var j = i % 2;

    ctx.fillStyle = "rgb(0,255,0)";
    ctx.fillRect(25, 25, 100, 100);

    ctx.fillStyle = "rgba(255,0,0, 0.6)";
    ctx.beginPath();
    ctx.arc(j*30+125,(1-j)*30+100,50,0,Math.PI*2,true);
    ctx.fill();

    ctx.fillStyle = "rgba(0,0,255,0.6)";
    ctx.beginPath();
    ctx.moveTo(125,100);
    ctx.lineTo(175,50);
    ctx.lineTo(225,150);
    ctx.fill();
    
    drawBatman(ctx);
    
    i++;
}

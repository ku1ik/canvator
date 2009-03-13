var Canvator = {
  ctx: null,
  width: null,
  height: null,
  HCENTER: null,
  VCENTER: null,
  bg: new Image(),
  sprite: new Image(),
  i: 0,

  init: function() {
    var canvasElement = document.getElementById('example');
    this.ctx = canvasElement.getContext('2d');
    this.width = canvasElement.getAttribute("width") * 1;
    this.height = canvasElement.getAttribute("height") * 1;
    this.HCENTER = this.width / 2;
    this.VCENTER = this.height / 2;
    this.loadGraphics();
    setInterval(function() { Canvator.draw.apply(Canvator) }, 1333);
  },

  loadGraphics: function() {
    this.bg.src = "gfx/buildings.gif";
    this.sprite.src = "gfx/batman.png";
  },

  draw: function() {
    this.clear();
    //ctx.globalCompositeOperation = 'lighter';

    var j = this.i % 2;

    this.ctx.fillStyle = "rgb(0,255,0)";
    this.ctx.fillRect(25, 25, 100, 100);

    this.ctx.fillStyle = "rgba(255,0,0, 0.6)";
    this.ctx.beginPath();
    this.ctx.arc(j*30+125,(1-j)*30+100,50,0,Math.PI*2,true);
    this.ctx.fill();

    this.ctx.fillStyle = "rgba(0,0,255,0.6)";
    this.ctx.beginPath();
    this.ctx.moveTo(125,100);
    this.ctx.lineTo(175,50);
    this.ctx.lineTo(225,150);
    this.ctx.fill();

    this.drawBatman();

    this.i++;
  },

  clear: function() {
//    this.ctx.clearRect(0, 0, this.width, this.height);
    //    ctx.globalCompositeOperation = 'source-over';
    this.ctx.drawImage(this.bg, 0, 0);
  },

  drawBatman: function() {
    this.ctx.save();
    this.ctx.translate(this.HCENTER, this.VCENTER);
    this.ctx.rotate(this.i);
    this.ctx.drawImage(this.sprite, 0, 0, 90, 30);
    this.ctx.restore();
  }

}


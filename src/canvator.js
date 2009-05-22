var Canvator = {
  fps: 20,
  running: false,
  ctx: null,
  width: null,
  height: null,
  HCENTER: null,
  VCENTER: null,
  bg: new Image(),
  sprite: new Image(),
  overlay: new Image(),
  superman: new Image(),
  i: 0,

  init: function() {
    var canvasElement = document.getElementById('example');
    canvasElement.onclick = function() {
      if (!this.running) {
        this.running = true;
        setInterval(function() { Canvator.draw.apply(Canvator) }, 1000 / Canvator.fps);
      }
    };
    this.ctx = canvasElement.getContext('2d');
    this.width = canvasElement.getAttribute("width") * 1;
    this.height = canvasElement.getAttribute("height") * 1;
    this.HCENTER = this.width / 2;
    this.VCENTER = this.height / 2;
    this.loadGraphics();
    this.ctx.font = '30px Georgia';
    this.ctx.globalAlpha = 0.5;
    this.draw();
  },

  loadGraphics: function() {
    this.bg.src = "gfx/bg.jpg";
    this.sprite.src = "gfx/batman.png";
    this.overlay.src = "gfx/overlay.png";
    this.superman.src = "gfx/superman.png";
  },

  draw: function() {
//    this.clear();
    this.drawBg();
    //ctx.globalCompositeOperation = 'lighter';
    this.drawSuperman();
    this.drawBatman();
    this.drawOverlay();
    this.drawDashboard();

    this.i++;
  },

//  clear: function() {
//    this.ctx.clearRect(0, 0, this.width, this.height);
    //    ctx.globalCompositeOperation = 'source-over';
//  },

  drawBg: function() {
    this.ctx.save();
    this.ctx.translate(this.HCENTER, this.VCENTER);
    var x = - (this.bg.width / 2) - Math.sin(2 * this.i * Math.PI/180) * 50.0;
    var y = - (this.bg.height / 2) + Math.cos(2 * this.i * Math.PI/180) * 170.0;
    this.ctx.drawImage(this.bg, x, y);
    this.ctx.restore();
  },

  drawSuperman: function() {
    this.ctx.save();
    var scale = 0.7;
    var horizon = 50 + Math.cos(2 * this.i * Math.PI/180) * 170.0;
    this.ctx.translate((this.i * 3) % 1000, horizon);
    this.ctx.scale(scale, scale);
    this.ctx.drawImage(this.superman, - this.sprite.width / 2, - this.sprite.height / 2, this.sprite.width, this.sprite.height);
    this.ctx.restore();
  },

  drawBatman: function() {
    var alpha = this.ctx.globalAlpha;// = 0.8;
    this.ctx.globalAlpha = 1.0;
    this.ctx.save();
    this.ctx.translate(this.HCENTER, this.VCENTER);
    var angle = 3 * this.i * Math.PI/180;// * (1 + Math.sin(this.i / 3 * Math.PI/180) * 0.5);
    this.ctx.rotate(angle);
    var x = - (this.sprite.width / 2) - Math.sin(3 * this.i * Math.PI/180) * 100.0;
    var y = - (this.sprite.height / 2) + Math.cos(3 * this.i * Math.PI/180) * 100.0;
    var scale = 0.51 + Math.cos(this.i * Math.PI/180) * 0.5;
    this.ctx.scale(scale, scale);
    this.ctx.drawImage(this.sprite, x, y, this.sprite.width, this.sprite.height);
    this.ctx.restore();
    this.ctx.globalAlpha = alpha;
  },

  drawOverlay: function() {
    this.ctx.drawImage(this.overlay, 0, 0);
  },

  drawDashboard: function() {
    this.ctx.save();
    this.ctx.translate(57, 280);
//    var angle = this.i / 3 * Math.PI/180;
//    this.ctx.rotate(angle);
    var delta = 0.51 + Math.cos((-180 + this.i * 2) * Math.PI/180) * 0.5; //(this.i % 100) / 100.0;
    this.ctx.scale(1.0, 0.01 + delta);
    this.ctx.fillStyle = "rgba(0, 0, 0, " + delta + ")";
    if (this.ctx.fillText) {
        this.ctx.fillText('Battle of Superheroes!', 10, 10);
    } else {
        this.ctx.mozDrawText('Battle of Superheroes!', 10, 10);
    }
    this.ctx.restore();
  }
}

package game
{
	import game.CorpusculaGame;
	
	public class Corpuscula
	{
		var x:Number;
		var y:Number;
		var width:Number;
		var height:Number;
		var dX:Number;
		var dY:Number;
		var proton:Proton = new Proton();
		var handle:MouseHandle = new MouseHandle();
		var corpGame:CorpusculaGame;
		var child0:Corpuscula;
		var child1:Corpuscula;
		
		public function Corpuscula(_game:CorpusculaGame):void
		{
			corpGame = _game;
			width = proton.width;
			height = proton.height;
			x = y = dX = dY = 0;
		}
		
		public function SetPosition(_x:Number, _y:Number):void
		{
			x = _x; y = _y;
		}
		
		public function StartEdit():void
		{
			//
			corpGame.addChild(handle);
			handle.x = x;
			handle.y = y;
			//
			corpGame.addChild(proton);
			proton.x = x;
			proton.y = y;
			
			if (child0) child0.StartEdit();
			if (child1) child1.StartEdit();
		}
		
		public function StopEdit():void
		{
			corpGame.removeChild(proton);
			
			if (child0) child0.StopEdit();
			if (child1) child1.StopEdit();
		}
		
		public function Update():void
		{
			proton.x = x - width / 2;
			proton.y = y - height / 2;
		}
	}
}
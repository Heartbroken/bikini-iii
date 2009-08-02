package game
{
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import lib.fsm.*;
	
	public class CorpusculaGame extends MovieClip
	{
		// Dynamic props
		var m_props:Object = new Object();
		
		// FSM states
		var m_stateInit:FSMState = new FSMState(BeginInit, UpdateInit, EndInit);
		var m_stateEdit:FSMState = new FSMState(BeginEdit, UpdateEdit, EndEdit);
		var m_statePlay:FSMState = new FSMState(BeginPlay, UpdatePlay, EndPlay);
		var m_fsm:FSM;
		
		// Root corpusculas
		var m_roots:Array = new Array();
		
		// Selected corpuscula
		var m_selected:Corpuscula;
		
		// Corpuscula editor
		var m_editor:Editor = new Editor();
		
		// Constructor
		public function CorpusculaGame():void
		{
			m_fsm = new FSM(m_stateInit);
		}
		
		// Get/Set selected corpuscula
		public function GetSelected():Corpuscula
		{
			return m_selected;
		}
		public function SetSelected(_corpuscula:Corpuscula):void
		{
			if (m_selected) m_selected.Unselect();
			m_selected = _corpuscula;
			if (m_selected) m_selected.Select();
		}
		
		// Editor accessor
		public function GetEditor():Editor
		{
			return m_editor;
		}
		
		// Adding/Removing
		public function AddEntity(_child:DisplayObject):void
		{
			world.addChild(_child);
		}
		public function RemoveEntity(_child:DisplayObject):void
		{
			if (world.contains(_child)) world.removeChild(_child);
		}
		public function AddTrack(_child:DisplayObject):void
		{
			scheme.addChild(_child);
		}
		public function RemoveTrack(_child:DisplayObject):void
		{
			if (scheme.contains(_child)) scheme.removeChild(_child);
		}
		public function AddHotspot(_child:DisplayObject):void
		{
			hotspots.addChild(_child);
		}
		public function RemoveHotspot(_child:DisplayObject):void
		{
			if (hotspots.contains(_child)) hotspots.removeChild(_child);
		}
		
		// Update
		function Update(event:Event):void
		{
			m_fsm.Update();
		}
		
		// State Init ///////////////////////////////////////////////////////////////////////////////////
		function BeginInit():void
		{
			scheme.addChild(new InitLoading()).name = "InitLoading";
			addEventListener(Event.ENTER_FRAME, Update);
			m_props.initDelay = 30;
		}
		function UpdateInit():void
		{
			if (--m_props.initDelay == 0) m_fsm.SetState(m_stateEdit);
		}
		function EndInit():void
		{
			scheme.removeChild(scheme.getChildByName("InitLoading"));
			delete m_props.initDelay;
			var l_root:Corpuscula = new Corpuscula(this);
			m_roots.push(l_root);
			m_editor.visible = false;
		}
		
		// State Edit ///////////////////////////////////////////////////////////////////////////////////
		function BeginEdit():void
		{
			editor.addChild(m_editor);
			for each (var l_root:Corpuscula in m_roots) l_root.StartEdit();
		}
		function UpdateEdit():void
		{
		}
		function EndEdit():void
		{
			for each (var l_root:Corpuscula in m_roots) l_root.StopEdit();
			editor.removeChild(m_editor);
		}

		// State Play ///////////////////////////////////////////////////////////////////////////////////
		function BeginPlay():void
		{
		}
		function UpdatePlay():void
		{
		}
		function EndPlay():void
		{
		}
	}
}
	
// Internals //////////////////////////////////////////////////////////////////////////////////////

import flash.events.MouseEvent;
import flash.display.Sprite;
import flash.geom.Point;
import flash.geom.Matrix;
import game.CorpusculaGame;

// 
class Corpuscula
{
	// Dynamic props
	var m_props:Object = new Object();
	
	var m_position:Point = new Point();
	var m_velocity:Point = new Point();
//	var m_x:Number = 0;
//	var m_y:Number = 0;
//	var m_velX:Number = 0;
//	var m_velY:Number = 0;
	var m_fissTime:Number = Infinity;
	var m_fissAngle:Number = 0;
	var m_selector:Selector = new Selector();
	var m_proton:Proton = new Proton();
//	var handle:MouseHandle = new MouseHandle();
	var m_track:Sprite = new Sprite();
	var m_game:CorpusculaGame;
	var m_parent:Corpuscula;
	var m_child0:Corpuscula;
	var m_child1:Corpuscula;
	
	public function Corpuscula(_game:CorpusculaGame, _parent:Corpuscula = null):void
	{
		m_game = _game;
		m_parent = _parent;
	}
	
	public function SetPosition(_position:Point):void
	{
		m_position = _position.clone();
	}
	
	public function SetVelocity(_velocity:Point):void
	{
		m_velocity = _velocity.clone();
	}
	
	public function StartEdit():void
	{
		if (m_parent == null)
		{
			m_game.AddEntity(m_proton);
			m_proton.x = m_position.x;
			m_proton.y = m_position.y;
		}
		
		if (isFinite(m_fissTime))
		{
		}
		else
		{
			if (Point.distance(m_velocity, new Point()) > Number.MIN_VALUE)
			{
				m_game.AddTrack(m_track);
				m_track.x = m_position.x;
				m_track.y = m_position.y;
				m_track.graphics.lineStyle(10, 0x777777);
				m_track.graphics.lineTo(m_velocity.x * 100, m_velocity.y * 100);
				m_track.buttonMode = true;
			}
			else
			{
				m_game.AddHotspot(m_selector);
				m_selector.x = m_position.x;
				m_selector.y = m_position.y;
				m_selector.addEventListener(MouseEvent.CLICK, OnSelectorClick);
			}
		}
		
//		var l_x:Number = x + dX;
//		var l_y:Number = y + dY;
//		//
//		m_game.screen.addChild(track);
//		track.x = x;
//		track.y = y;
//		track.graphics.lineStyle(10, 0x777777);
//		track.graphics.lineTo(dX, dY);
//		track.buttonMode = true;
//		//
//		m_game.screen.addChild(proton);
//		proton.x = l_x;
//		proton.y = l_y;
//		//
//		m_game.screen.addChild(handle);
//		handle.x = l_x;
//		handle.y = l_y;
		
		if (m_child0) m_child0.StartEdit();
		if (m_child1) m_child1.StartEdit();
	}
	
	public function StopEdit():void
	{
		m_game.RemoveTrack(m_track);
		m_selector.removeEventListener(MouseEvent.CLICK, OnSelectorClick);
		m_game.RemoveHotspot(m_selector);
		
//		m_game.screen.removeChild(track);
//		m_game.screen.removeChild(proton);
//		m_game.screen.removeChild(handle);
		
		if (m_child0) m_child0.StopEdit();
		if (m_child1) m_child1.StopEdit();
	}
	
	public function Update():void
	{
//		proton.x = x - width / 2;
//		proton.y = y - height / 2;
	}
	
	function OnSelectorClick(event:MouseEvent):void
	{
		m_game.SetSelected(this);
	}
	
	public function Select():void
	{
		m_selector.visible = false;
		var l_editor:Editor = m_game.GetEditor();
		l_editor.x = m_position.x;
		l_editor.y = m_position.y;
		l_editor.rotation = m_fissAngle * 180 / Math.PI;
		l_editor.rotationHandle.addEventListener(MouseEvent.MOUSE_DOWN, OnRotationDown);
		l_editor.split0Handle.addEventListener(MouseEvent.CLICK, OnSplitClick);
		l_editor.split1Handle.addEventListener(MouseEvent.CLICK, OnSplitClick);
		l_editor.visible = true;
	}
	public function Unselect():void
	{
		m_selector.visible = true;
		var l_editor:Editor = m_game.GetEditor();
		l_editor.visible = false;
		l_editor.rotationHandle.removeEventListener(MouseEvent.MOUSE_DOWN, OnRotationDown);
		l_editor.split0Handle.removeEventListener(MouseEvent.CLICK, OnSplitClick);
		l_editor.split1Handle.removeEventListener(MouseEvent.CLICK, OnSplitClick);
	}
	
	function OnSplitClick(_event:MouseEvent):void
	{
		if (m_child0)
		{
			m_child0.StopEdit();
			m_child0 = null;
			m_child1.StopEdit();
			m_child1 = null;
		}
		else
		{
			m_child0 = new Corpuscula(m_game, this);
			m_child0.SetVelocity(new Point(0, -100));
			m_child0.StartEdit();
			m_child1 = new Corpuscula(m_game, this);
			m_child1.SetVelocity(new Point(0, 100));
			m_child1.StartEdit();
		}
	}
	
	function OnRotationDown(_event:MouseEvent):void
	{
		var l_editor:Editor = m_game.GetEditor();
		var l_centre:Point = l_editor.localToGlobal(new Point());
		var l_angle:Number = Math.atan2(_event.stageY - l_centre.y, _event.stageX - l_centre.x);
		m_props.rotationAngle = l_angle;
		m_game.stage.addEventListener(MouseEvent.MOUSE_MOVE, OnRotationMove);
		m_game.stage.addEventListener(MouseEvent.MOUSE_UP, OnRotationUp);
	}
	function OnRotationMove(_event:MouseEvent):void
	{
		if (m_props.rotationAngle is Number)
		{
			var l_editor:Editor = m_game.GetEditor();
			var l_centre:Point = l_editor.localToGlobal(new Point());
			var l_angle:Number = Math.atan2(_event.stageY - l_centre.y, _event.stageX - l_centre.x);
			m_fissAngle += l_angle - m_props.rotationAngle;
			l_editor.rotation += (l_angle - m_props.rotationAngle) * 180 / Math.PI;
			m_props.rotationAngle = l_angle;
		}
	}
	function OnRotationUp(_event:MouseEvent):void
	{
		delete m_props.rotationAngle;
		m_game.stage.removeEventListener(MouseEvent.MOUSE_MOVE, OnRotationMove);
		m_game.stage.removeEventListener(MouseEvent.MOUSE_UP, OnRotationUp);
	}
}

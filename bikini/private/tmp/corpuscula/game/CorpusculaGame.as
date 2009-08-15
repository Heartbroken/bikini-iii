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
			l_root.SetMass(20);
			m_roots.push(l_root);
			m_editor.visible = false;
		}
		
		// State Edit ///////////////////////////////////////////////////////////////////////////////////
		function BeginEdit():void
		{
			editor.addChild(m_editor);
			for each (var l_root:Corpuscula in m_roots) l_root.StartEdit();
			stage.addEventListener(MouseEvent.CLICK, OnStageClick);
		}
		function UpdateEdit():void
		{
		}
		function EndEdit():void
		{
			for each (var l_root:Corpuscula in m_roots) l_root.StopEdit();
			editor.removeChild(m_editor);
			stage.removeEventListener(MouseEvent.CLICK, OnStageClick);
		}
		function OnStageClick(_event:MouseEvent):void
		{
			if (_event.target == stage) SetSelected(null);
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
//import flash.display.Sprite;
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
	var m_mass:uint = 1;
//	var m_x:Number = 0;
//	var m_y:Number = 0;
//	var m_velX:Number = 0;
//	var m_velY:Number = 0;
	var m_fissTime:Number = Infinity;
	var m_fissAngle:Number = 0;
	var m_selector:Selector = new Selector();
	var m_proton:Proton = new Proton();
//	var handle:MouseHandle = new MouseHandle();
	var m_track:Track = new Track();
	var m_game:CorpusculaGame;
	var m_parent:Corpuscula;
	var m_child0:Corpuscula;
	var m_child1:Corpuscula;
	
	public function Corpuscula(_game:CorpusculaGame, _parent:Corpuscula = null):void
	{
		m_game = _game;
		m_parent = _parent;
		m_track.selectorHandle.visible = false;
	}
	
	public function Position():Point { return m_position.clone(); }
	public function SetPosition(_position:Point):void { m_position = _position.clone(); }
	public function Velocity():Point { return m_velocity.clone(); }
	public function SetVelocity(_velocity:Point):void { m_velocity = _velocity.clone(); }
	public function Mass():uint { return m_mass; }
	public function SetMass(_mass:uint):void { m_mass = _mass; }
	
	public function FissPosition():Point
	{
		var l_time:Number = m_fissTime;
//		if (!m_child0 || !m_child1) l_time = Infinity;
		if (m_velocity.length < Number.MIN_VALUE) l_time = 0;
		if (!isFinite(l_time)) l_time = 1000 / m_velocity.length;
		var l_pos:Point = Point.interpolate(m_position.add(m_velocity), m_position, l_time);
		return l_pos;
	}
	
	public function StartEdit():void
	{
		m_game.AddEntity(m_proton);
		m_game.AddTrack(m_track);
		m_game.AddHotspot(m_selector);
		m_selector.addEventListener(MouseEvent.CLICK, OnSelectorClick);
		
		if (m_child0) m_child0.StartEdit();
		if (m_child1) m_child1.StartEdit();
	}
	
	public function StopEdit():void
	{
		m_game.RemoveEntity(m_proton);
		m_game.RemoveTrack(m_track);
		m_game.RemoveHotspot(m_selector);
		
		m_selector.removeEventListener(MouseEvent.CLICK, OnSelectorClick);
		
		m_track.removeEventListener(MouseEvent.MOUSE_MOVE, OnTrackMove);
		m_track.removeEventListener(MouseEvent.CLICK, OnTrackClick);
		m_track.removeEventListener(MouseEvent.MOUSE_OUT, OnTrackOut);
		
		if (!m_child0 && !m_child1) m_fissTime = Infinity;
		
		if (m_child0) m_child0.StopEdit();
		if (m_child1) m_child1.StopEdit();
	}
	
	function UpdateEdit():void
	{
		m_proton.visible = false;
		m_track.visible = false;
		m_selector.visible = false;
		m_track.graphics.clear();
		m_track.selectorHandle.visible = false;
		
		if (m_parent == null) m_proton.visible = true;

		if (m_child0 && m_child1)
		{
			var l_mass0Part:Number = Number(m_child0.Mass()) / Number(m_child0.Mass() + m_child1.Mass());
			var l_mass0:uint = l_mass0Part * m_mass + 0.5;
			var l_mass1:uint = m_mass - l_mass0;
			if (l_mass0 == 0 || l_mass1 == 0)
			{
				m_child0.StopEdit();
				m_child0 = null;
				m_child1.StopEdit();
				m_child1 = null;
				m_fissTime = Infinity;
			}
			else
			{
				m_child0.SetMass(l_mass0);
				m_child1.SetMass(l_mass1);
			}
		}
		
		if (m_velocity.length > Number.MIN_VALUE)
		{
			m_track.x = m_position.x;
			m_track.y = m_position.y;
			var l_fissTime:Number = m_fissTime;
			if (!m_child0 && !m_child1) m_fissTime = Infinity;
			var l_fissPos:Point = FissPosition();
			m_fissTime = l_fissTime;
			m_selector.x = l_fissPos.x;
			m_selector.y = l_fissPos.y;
			if (m_game.GetSelected() != this) m_selector.visible = true;
			l_fissPos = l_fissPos.subtract(m_position);
//			var l_thickness:Number = Math.sqrt(m_mass / Math.PI) * 7;
			var l_thickness:Number = Math.pow((3 * m_mass) / (4 * Math.PI), 1 / 3) * 7;
			m_track.graphics.lineStyle(20, 0, 0);
			m_track.graphics.lineTo(l_fissPos.x, l_fissPos.y);
			m_track.graphics.moveTo(0, 0);
			m_track.graphics.lineStyle(l_thickness, 0x777777, m_mass > 1 ? 1 : 1);
			m_track.graphics.lineTo(l_fissPos.x, l_fissPos.y);
			m_track.graphics.moveTo(0, 0);
//			m_track.graphics.lineStyle(0, 0, 0);
//			m_track.graphics.beginFill(0x777777);
//			m_track.graphics.drawCircle(l_fissPos.x, l_fissPos.y, l_thickness * 0.55);
//			m_track.graphics.endFill();
			m_track.graphics.lineStyle(1, 0x555555);
			var l_step:Point = m_velocity.clone(); l_step.normalize(3);
			var l_space:Point = m_velocity.clone(); l_space.normalize(m_velocity.length * 5);
			var l_currPnt:Point = new Point(); //m_velocity.clone(); l_currPnt.normalize(10);
			while(l_currPnt.length < l_fissPos.length)
			{
				m_track.graphics.moveTo(l_currPnt.x, l_currPnt.y);
				//l_currPnt = l_currPnt.add(l_step);
				m_track.graphics.drawCircle(l_currPnt.x, l_currPnt.y, 0.3);
				//m_track.graphics.lineTo(l_currPnt.x, l_currPnt.y);
				l_currPnt = l_currPnt.add(l_space);
			}
			m_track.visible = true;
			if (m_mass > 1)
			{
				m_track.buttonMode = true;
				m_track.addEventListener(MouseEvent.MOUSE_MOVE, OnTrackMove);
				m_track.addEventListener(MouseEvent.CLICK, OnTrackClick);
				m_track.addEventListener(MouseEvent.MOUSE_OUT, OnTrackOut);
			}
			else
			{
				m_track.buttonMode = false;
				m_track.removeEventListener(MouseEvent.MOUSE_MOVE, OnTrackMove);
				m_track.removeEventListener(MouseEvent.CLICK, OnTrackClick);
				m_track.removeEventListener(MouseEvent.MOUSE_OUT, OnTrackOut);
			}
		}
		else
		{
			m_selector.x = m_position.x;
			m_selector.y = m_position.y;
			if (m_game.GetSelected() != this) m_selector.visible = true;
		}
		
		if (m_child0 && m_child1)
		{
			var l_pos:Point = FissPosition();
			m_child0.SetPosition(l_pos);
			m_child1.SetPosition(l_pos);
			
			var l_dir:Point = new Point(0, 1);
			var l_baseAngle:Number = 0;
			if (m_velocity.length > Number.MIN_VALUE) l_baseAngle = Math.atan2(m_velocity.y, m_velocity.x);
			var l_rotate:Matrix = new Matrix();
			l_rotate.rotate(l_baseAngle + m_fissAngle);
			l_dir = l_rotate.transformPoint(l_dir);
			
			var l_energy:Number = 10;
			var l_vel0:Point = l_dir.clone(); l_vel0.normalize(Math.sqrt(l_energy / m_child0.Mass()));
			var l_vel1:Point = l_dir.clone(); l_vel1.normalize(Math.sqrt(l_energy / m_child1.Mass()));
			
			m_child0.SetVelocity(m_velocity.subtract(l_vel0));
			m_child1.SetVelocity(m_velocity.add(l_vel1));
			
			m_child0.UpdateEdit();
			m_child1.UpdateEdit();
		}
	}
	
	public function Update():void
	{
//		proton.x = x - width / 2;
//		proton.y = y - height / 2;
	}
	
	function OnTrackMove(_event:MouseEvent):void
	{
		var l_pos:Point = m_velocity.clone(); l_pos.normalize(1);
		var l_pnt:Point = new Point(_event.localX, _event.localY);
		var l_dot:Number = l_pos.x * l_pnt.x + l_pos.y * l_pnt.y;
		l_pos.normalize(l_dot);
		m_track.selectorHandle.x = l_pos.x;
		m_track.selectorHandle.y = l_pos.y;
		m_track.selectorHandle.visible = true;
	}
	function OnTrackClick(_event:MouseEvent):void
	{
		var l_pos:Point = m_velocity.clone(); l_pos.normalize(1);
		var l_pnt:Point = new Point(_event.localX, _event.localY);
		var l_dot:Number = l_pos.x * l_pnt.x + l_pos.y * l_pnt.y;
		l_pos.normalize(l_dot);
		m_fissTime = l_pos.length / m_velocity.length;
		m_game.SetSelected(this);
		UpdateEdit();
	}
	function OnTrackOut(_event:MouseEvent):void
	{
		m_track.selectorHandle.visible = false;
	}
	
	function OnSelectorClick(_event:MouseEvent):void
	{
		m_game.SetSelected(this);
	}
	
	public function Select():void
	{
		m_selector.visible = false;
		var l_editor:Editor = m_game.GetEditor();
		var l_pos:Point = FissPosition();
		l_editor.x = l_pos.x;
		l_editor.y = l_pos.y;
		var l_baseAngle:Number = 0;
		if (m_velocity.length > Number.MIN_VALUE) l_baseAngle = Math.atan2(m_velocity.y, m_velocity.x);
		l_editor.rotation = (l_baseAngle + m_fissAngle) * 180 / Math.PI;
		l_editor.rotationHandle.addEventListener(MouseEvent.MOUSE_DOWN, OnRotationDown);
		l_editor.split0Handle.addEventListener(MouseEvent.MOUSE_DOWN, OnSplitDown);
		l_editor.split1Handle.addEventListener(MouseEvent.MOUSE_DOWN, OnSplitDown);
		l_editor.moveHandle.addEventListener(MouseEvent.MOUSE_DOWN, OnMoveDown);
		l_editor.visible = true;
	}
	public function Unselect():void
	{
		m_selector.visible = true;
		var l_editor:Editor = m_game.GetEditor();
		l_editor.visible = false;
		l_editor.rotationHandle.removeEventListener(MouseEvent.MOUSE_DOWN, OnRotationDown);
		l_editor.split0Handle.removeEventListener(MouseEvent.MOUSE_DOWN, OnSplitDown);
		l_editor.split1Handle.removeEventListener(MouseEvent.MOUSE_DOWN, OnSplitDown);
		l_editor.moveHandle.removeEventListener(MouseEvent.MOUSE_DOWN, OnMoveDown);
	}

	
	function OnMoveDown(_event:MouseEvent):void
	{
		m_game.stage.addEventListener(MouseEvent.MOUSE_MOVE, OnMoveMove);
		m_game.stage.addEventListener(MouseEvent.MOUSE_UP, OnMoveUp);
	}
	function OnMoveMove(_event:MouseEvent):void
	{
		var l_pos:Point = m_game.world.localToGlobal(Position());
		var l_dir:Point = m_velocity.clone(); l_dir.normalize(1);
		var l_pnt:Point = new Point(_event.stageX, _event.stageY);
		l_pnt = l_pnt.subtract(l_pos);
		var l_dot:Number = Math.max(0, l_dir.x * l_pnt.x + l_dir.y * l_pnt.y);
		l_dir.normalize(l_dot);
		l_pos = m_game.world.globalToLocal(l_pos.add(l_dir));
		var l_editor:Editor = m_game.GetEditor();
		l_editor.x = l_pos.x;
		l_editor.y = l_pos.y;
		m_fissTime = l_dir.length / m_velocity.length;
		UpdateEdit();
	}
	function OnMoveUp(_event:MouseEvent):void
	{
		m_game.stage.removeEventListener(MouseEvent.MOUSE_MOVE, OnMoveMove);
		m_game.stage.removeEventListener(MouseEvent.MOUSE_UP, OnMoveUp);
	}
	
	function OnSplitDown(_event:MouseEvent):void
	{
		if (m_mass == 1) return;
		
		var l_editor:Editor = m_game.GetEditor();
		
		if (m_child0 == null && m_child1 == null)
		{
			var l_fissPos:Point = FissPosition();
			m_child0 = new Corpuscula(m_game, this);
			m_child0.SetPosition(l_fissPos);
			m_child0.StartEdit();
			m_child1 = new Corpuscula(m_game, this);
			m_child1.SetPosition(l_fissPos);
			m_child1.StartEdit();
			
			if (_event.target == l_editor.split0Handle)
			{
				m_child0.SetMass(0);
				m_child1.SetMass(m_mass);
			}
			else
			{
				m_child0.SetMass(m_mass);
				m_child1.SetMass(0);
			}

		}
		
		if (_event.target == l_editor.split0Handle)
		{
			m_child0.SetMass(m_child0.Mass() + 1);
			m_child1.SetMass(m_child1.Mass() - 1);
		}
		else
		{
			m_child0.SetMass(m_child0.Mass() - 1);
			m_child1.SetMass(m_child1.Mass() + 1);
		}

		if (m_child0.Mass() == 0 || m_child1.Mass() == 0)
		{
			m_child0.StopEdit();
			m_child0 = null;
			m_child1.StopEdit();
			m_child1 = null;
		}
		
		UpdateEdit();

		if (m_child0 && m_child1)
		{
			m_props.splitHandle = (_event.target == l_editor.split0Handle) ? 0 : 1;
			var l_dir:Point = new Point(0, 1);
			var l_rot:Matrix = new Matrix(); l_rot.rotate(l_editor.rotation * Math.PI / 180);
			l_dir = l_rot.transformPoint(l_dir);
			var l_pnt:Point = new Point(_event.stageX, _event.stageY);
			var l_proj:Number = l_dir.x * l_pnt.x + l_dir.y * l_pnt.y;
			m_props.splitProj = l_proj;
			m_game.stage.addEventListener(MouseEvent.MOUSE_MOVE, OnSplitMove);
			m_game.stage.addEventListener(MouseEvent.MOUSE_UP, OnSplitUp);
		}
	}
	function OnSplitMove(_event:MouseEvent):void
	{
		if (m_props.splitProj is Number)
		{
			var l_editor:Editor = m_game.GetEditor();
			var l_dir:Point = new Point(0, 1);
			var l_rot:Matrix = new Matrix(); l_rot.rotate(l_editor.rotation * Math.PI / 180);
			l_dir = l_rot.transformPoint(l_dir);
			var l_pnt:Point = new Point(_event.stageX, _event.stageY);
			var l_proj:Number = l_dir.x * l_pnt.x + l_dir.y * l_pnt.y;
			var l_diff:Number = l_proj - m_props.splitProj;
			if (Math.abs(l_diff) > Number.MIN_VALUE)
			{
				var l_step:Number = 5 * l_diff / Math.abs(l_diff);
				var l_add:int = l_step > 0 ? -1 : 1;
				//if (m_props.splitHandle) l_add = -l_add;
				while(Math.abs(l_diff) > Math.abs(l_step))
				{
					if (m_child0.Mass() + l_add > 0 && m_child1.Mass() - l_add > 0)
					{
						m_child0.SetMass(m_child0.Mass() + l_add);
						m_child1.SetMass(m_child1.Mass() - l_add);
						l_diff -= l_step;
						m_props.splitProj += l_step;
					}
					else
						l_diff = 0;
				}
			}
			
			UpdateEdit();
		}
	}
	function OnSplitUp(_event:MouseEvent):void
	{
		delete m_props.splitProj;
		m_game.stage.removeEventListener(MouseEvent.MOUSE_MOVE, OnSplitMove);
		m_game.stage.removeEventListener(MouseEvent.MOUSE_UP, OnSplitUp);
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

			if (m_child0 && m_child1)
			{
				UpdateEdit();
			}
		}
	}
	function OnRotationUp(_event:MouseEvent):void
	{
		delete m_props.rotationAngle;
		m_game.stage.removeEventListener(MouseEvent.MOUSE_MOVE, OnRotationMove);
		m_game.stage.removeEventListener(MouseEvent.MOUSE_UP, OnRotationUp);
	}
}

package lib.fsm
{
	public class FSMState
	{
		public var BeginState:Function;
		public var UpdateState:Function;
		public var EndState:Function;
		
		public function FSMState(_beginState:Function, _updateState:Function, _endState:Function)
		{
			BeginState = _beginState;
			UpdateState = _updateState;
			EndState = _endState;
		}
	}
}
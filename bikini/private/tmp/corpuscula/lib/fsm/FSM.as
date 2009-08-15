package lib.fsm
{
	import lib.fsm.FSMState;
	
	public class FSM
	{
		var currState:FSMState;
		var nextState:FSMState;
		var lockState:Boolean = false;

		public function FSM(_currState:FSMState)
		{
			currState = _currState;
			currState.BeginState();
		}
		
		public function SetState(_nextState:FSMState):Boolean
		{
			if (lockState) return false;
			nextState = _nextState;
			return true;
		}
		
		public function StateIs(_testState:FSMState):Boolean
		{
			if (nextState != null) return nextState == _testState;
			return currState == _testState;
		}
		
		public function Update():void
		{
			if (nextState != null)
			{
				lockState = true;
				currState.EndState();
				currState = nextState;
				nextState = null;
				currState.BeginState();
				lockState = false;
			}
			currState.UpdateState();
		}
	}
}
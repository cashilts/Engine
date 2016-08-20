#pragma once
class GameState {
	public:
		virtual void Update();
		virtual void OnStateEnter();
		virtual void OnStateExit();
};
#ifndef STATE_H
#define STATE_H

class State {

public:

    State() {};
    virtual ~State() {};
    virtual void Update(float elapsedTime) {};
    virtual void RenderScene() {};
    virtual void OnEnter() {};
    virtual void OnExit() {};
    virtual bool IsGameExit() {

		return false;
    }
};

#endif // STATE_H

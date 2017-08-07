#ifndef STATE_H
#define STATE_H

class State {

public:

    State();
    virtual ~State();

    virtual void Update(float elapsedTime) = 0;
    virtual void RenderScene() = 0;
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    virtual bool IsGameExit();
};

#endif // STATE_H

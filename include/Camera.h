#include "GameEngine.h"


class Camera{
public:
    Camera();
    void update(Vector2f);
    View getView();
private:
    View view;
    Vector2f position;
};
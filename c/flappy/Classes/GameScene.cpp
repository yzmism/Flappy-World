#include "GameScene.h"

USING_NS_CC;

Scene* FlappyGame::createScene()
{
    Scene* scene = Scene::create();
    Layer* layer = FlappyGame::create();

    scene->addChild(layer);
    
    return scene;
}

bool FlappyGame::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->windowSize = Director::getInstance()->getVisibleSize();
    this->generateWorld();
    this->addPlayer();
    this->setCameraTarget();

    return true;
}
/*
  Makes each individual layer and adds it to a ParallaxNode. The node is then added to the Scene. 
 */
void FlappyGame::generateWorld()
{
    this->parallaxNode = ParallaxNode::create();

    /*
     Anchor Point is a point that you set as a way to specifying what part
     of the Sprite will be used when setting the position of it. 
     (0, 0) - Bottom Left
     (0, 1) - Top Left
     (1, 0) - Bottom Right
     (1, 1) - Top right
     (0.5, 0.5) - Middle
    */
    this->parallaxNode->setAnchorPoint(Point::ZERO);

    // Create each layer separately, add it to the ParallaxNode. The Z level is automatically set to 0.0,
    // It doesn't matter because each layer will be part of the Node.
    this->generateBottomLayer();
    this->generateMiddleLayer();
    this->parallaxNode->addChild(this->bottomLayer, 0.0, Vec2(1, 1), Vec2::ZERO);
    this->parallaxNode->addChild(this->middleLayer, 0.0, Vec2(1, 1), Vec2::ZERO);

    // Adds parallaxNode to the Scene
    this->addChild(this->parallaxNode, 1);

    // use ->schedule to call different functions while the game is running. Starts the update game loop.
    // schedule() is a built in Cocos2d module
    this->schedule(schedule_selector(FlappyGame::updateScene));
}

/*
  Creates a basic background.
 */
void FlappyGame::generateBottomLayer()
{
    this->bottomLayer = Layer::create();
    for (int i = 0; i < 100; i++) {
        this->backgroundImg = Sprite::create("basic_day.png");
        this->backgroundImg->setAnchorPoint(Point::ZERO);
        this->backgroundImg->setPosition(i * this->backgroundImg->getContentSize().width, 0);
        this->backgroundImg->setScale(SCALE_FACTOR);
        this->bottomLayer->addChild(this->backgroundImg, Z_BOTTOM_LAYER);
    }
}

void FlappyGame::generateMiddleLayer()
{
    this->middleLayer = Layer::create();
}

/*
  Creates the user's bird, setting it's location in the middle of the screen, this can be changed later.
  Birds/Objects should always be in the middle layer.
 */
void FlappyGame::addPlayer()
{
    this->player = PlayerBird::create();
    this->player->retain();
    this->player->setPosition(this->getStartingLocation());
    this->middleLayer->addChild(this->player, Z_MIDDLE_LAYER);
}

/*
  "Follow" is the Cocos' class/function for cameras. Creates the camera and follows the main player. 
  Run action starts the camera.
 */
void FlappyGame::setCameraTarget()
{
    this->cameraTarget = Follow::create(this->player, Rect::ZERO);
    this->cameraTarget->retain();
    this->runAction(this->cameraTarget);
}

void FlappyGame::updateScene(float dt)
{
    this->updatePlayer(dt);
}

void FlappyGame::updatePlayer(float dt)
{
    this->player->update(dt);
}

Point FlappyGame::getStartingLocation()
{
    Size wSize = Director::getInstance()->getVisibleSize();
    Point start = Vec2(wSize.width/2, wSize.height/2);
    return start;
}

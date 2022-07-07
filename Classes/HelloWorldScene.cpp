#include "HelloWorldScene.h"
#include "GameOverScene.h"

USING_NS_CC; // макрос использования пространства имён cocos2d::

Scene* HelloWorld::createScene()
{
    // все указатели, которые порождает Cocos - 2dx уже находятся под контролем выделенной памяти. Поэтому они не требуют явного удаления через delete или обертки в интеллектуальный указатель
    auto scene = Scene::create(); // создаем сцену
    auto layer = HelloWorld::create(); // создаем слой сцены

    scene->addChild(layer); // добавляем слой как ребенка на сцену


    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init()) // если мы не можем проинициализировать - просто выходим
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize(); // получаем размеры вида просмотра (то, где будем рисовать)
    Vec2 origin = Director::getInstance()->getVisibleOrigin(); // получаем вектор смещения, для рисования на разных координатах

    this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float delta)
{
    time += delta;
    if (time >= 1.f)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        float x = random() % visibleSize.width;
        float y = random() % visibleSize.hight;

        auto touchListener = EventListenerTouchOneByOne::create();

        touchListener->onTouchBegan = [this](Touch* _touch, Event* event)-> bool {
            return onTouchBegan(_touch, event);
        };

        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        cocos2d::Sprite* sprite = cocos2d::Sprite::create("exp2.png");
        sprite->setPosition(Vec2(origin.x + x, origin.y + y));
        sprite->setContentSize(Size(100, 100));
        sprites.push_back(sprite);
        addChild(sprite, 0);
        sprite->setScale(0.95);

        if (sprites.size() > 10)
        {
            auto scene = GameOverScene::createScene();
            Director::getInstance()->pushScene(scene);
        }

        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite);
        time = 0.f;
    }
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* _event)
{
    //touch->getLocation(); // место нажатия
    //event->getCurrentTarget(); // на какой контрол мы кликнули, его адрес.
    //event->getCurrentTarget()->getBoundingBox(); // ограничивающий бокс вокруг контрола 

    auto bounds = _event->getCurrentTarget()->getBoundingBox();
    auto pos = touch->getLocation();
    if (!bounds.containsPoint(pos))
        return false;
    removeChild(_event->getCurrentTarget());
    sprites.clear();

    return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    cocos2d::log("touch ended"); // полезный метод: логирует вывод в консоль
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    cocos2d::log("touch moved");// полезный метод: логирует вывод в консоль
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
{
    cocos2d::log("touch cancelled");// полезный метод: логирует вывод в консоль
}
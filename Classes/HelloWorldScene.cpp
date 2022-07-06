#include "HelloWorldScene.h"
#include "GameOverScene.h"

USING_NS_CC; // ������ ������������� ������������ ��� cocos2d::

Scene* HelloWorld::createScene()
{
    // ��� ���������, ������� ��������� Cocos - 2dx ��� ��������� ��� ��������� ���������� ������. ������� ��� �� ������� ������ �������� ����� delete ��� ������� � ���������������� ���������
    auto scene = Scene::create(); // ������� �����
    auto layer = HelloWorld::create(); // ������� ���� �����

    scene->addChild(layer); // ��������� ���� ��� ������� �� �����


    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init()) // ���� �� �� ����� ������������������� - ������ �������
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize(); // �������� ������� ���� ��������� (��, ��� ����� ��������)
    Vec2 origin = Director::getInstance()->getVisibleOrigin(); // �������� ������ ��������, ��� ��������� �� ������ �����������

    this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float delta)
{
    time += delta;
    if (time >= 1.f)
    {
        float x = random() % 600;
        float y = random() % 500;

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
    //touch->getLocation(); // ����� �������
    //event->getCurrentTarget(); // �� ����� ������� �� ��������, ��� �����.
    //event->getCurrentTarget()->getBoundingBox(); // �������������� ���� ������ �������� 

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
    cocos2d::log("touch ended"); // �������� �����: �������� ����� � �������
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    cocos2d::log("touch moved");// �������� �����: �������� ����� � �������
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
{
    cocos2d::log("touch cancelled");// �������� �����: �������� ����� � �������
}
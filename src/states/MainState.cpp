#include "MainState.hpp"
#include "IntroState.hpp"

template<> MainState* Ogre::Singleton<MainState>::msSingleton = 0;

MainState* MainState::getSingletonPtr () {
    return msSingleton;
}

MainState& MainState::getSingleton () {
    assert (msSingleton);
    return *msSingleton;
}

void MainState::enter () {

}

void MainState::exit() {
    _root->getAutoCreatedWindow()->removeAllViewports();
}

void MainState::pause () {}

void MainState::resume () {}

bool MainState::frameStarted (const Ogre::FrameEvent &evt) {
    changeState(IntroState::getSingletonPtr());
    return true;
}

bool MainState::frameEnded (const Ogre::FrameEvent &evt) {
    return !_exit;
}

void MainState::keyPressed (const OIS::KeyEvent &e) {
    switch (e.key) {
        default:
            break;
    }
}

void MainState::keyReleased (const OIS::KeyEvent &e) {
    switch (e.key) {
        default:
            break;
    }
}

void MainState::mouseMoved (const OIS::MouseEvent &e) {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(e.state.X.abs, e.state.Y.abs);
}

void MainState::mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id) {}

void MainState::mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id) {}

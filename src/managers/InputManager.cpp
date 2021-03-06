#include "InputManager.h"

template<> InputManager* Ogre::Singleton<InputManager>::msSingleton = 0;

InputManager::InputManager ():
  _inputSystem(0),
  _keyboard(0),
  _mouse(0)
{
}

InputManager::~InputManager ()
{
  if (_inputSystem) {

    if (_keyboard) {
      _inputSystem->destroyInputObject(_keyboard);
      _keyboard = 0;
    }

    if (_mouse) {
      _inputSystem->destroyInputObject(_mouse);
      _mouse = 0;
    }

    OIS::InputManager::destroyInputSystem(_inputSystem);

    _inputSystem = 0;

    // Limpiar todos los listeners.
    _keyListeners.clear();
    _mouseListeners.clear();
    }
}

void
InputManager::initialise
(Ogre::RenderWindow *renderWindow)
{
  if(!_inputSystem) {
    // Setup basic variables
    OIS::ParamList paramList;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    renderWindow->getCustomAttribute("WINDOW", &windowHnd);
    // Fill parameter list
    windowHndStr << windowHnd;
    paramList.insert(std::make_pair(std::string( "WINDOW"),
				    windowHndStr.str()));
    paramList.insert(std::make_pair("x11_mouse_hide", std::string("true")));

#if defined OIS_WIN32_PLATFORM
    paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
    paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
    paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
    paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
    paramList.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    paramList.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
    paramList.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif

    // Create inputsystem
    _inputSystem = OIS::InputManager::
      createInputSystem(paramList);

    _keyboard = static_cast<OIS::Keyboard*>
      (_inputSystem->createInputObject(OIS::OISKeyboard, true));
    _keyboard->setEventCallback(this);

    _mouse = static_cast<OIS::Mouse*>
      (_inputSystem->createInputObject(OIS::OISMouse, true));
    _mouse->getMouseState().width = renderWindow->getWidth();
    _mouse->getMouseState().height = renderWindow->getHeight();
    _mouse->setEventCallback(this);

    // Get window size
    unsigned int width, height, depth;
    int left, top;
    renderWindow->getMetrics(width, height, depth, left, top);

    // Set mouse region
    this->setWindowExtents( width, height );
  }
}

void
InputManager::capture ()
{
  // Capturar y actualizar cada frame.
  if (_mouse)
    _mouse->capture();

  if (_keyboard)
    _keyboard->capture();
}

void
InputManager::addKeyListener
(OIS::KeyListener *keyListener, const std::string& instanceName)
{
  if (_keyboard) {
    // Comprobar si el listener existe.
    itKeyListener = _keyListeners.find(instanceName);
    if (itKeyListener == _keyListeners.end()) {
      _keyListeners[instanceName] = keyListener;
    }
    else {
      // Elemento duplicado; no hacer nada.
    }
  }
}

void
InputManager::addMouseListener
(OIS::MouseListener *mouseListener, const std::string& instanceName)
{
  if (_mouse) {
    // Comprobar si el listener existe.
    itMouseListener = _mouseListeners.find(instanceName);
    if (itMouseListener == _mouseListeners.end()) {
      _mouseListeners[instanceName] = mouseListener;
    }
    else {
      // Elemento duplicado; no hacer nada.
    }
  }
}

void
InputManager::removeKeyListener
(const std::string& instanceName)
{
  // Comprobar si el listener existe.
  itKeyListener = _keyListeners.find(instanceName);
  if (itKeyListener != _keyListeners.end()) {
    _keyListeners.erase(itKeyListener);
  }
  else {
    // No hacer nada.
  }
}

void
InputManager::removeMouseListener
(const std::string& instanceName)
{
  // Comprobar si el listener existe.
  itMouseListener = _mouseListeners.find(instanceName);
  if (itMouseListener != _mouseListeners.end()) {
    _mouseListeners.erase(itMouseListener);
  }
  else {
    // No hacer nada.
  }
}

void
InputManager::removeKeyListener
(OIS::KeyListener *keyListener)
{
  itKeyListener = _keyListeners.begin();
  itKeyListenerEnd = _keyListeners.end();
  for (; itKeyListener != itKeyListenerEnd; ++itKeyListener) {
    if (itKeyListener->second == keyListener) {
      _keyListeners.erase(itKeyListener);
      break;
    }
  }
}

void
InputManager::removeMouseListener
(OIS::MouseListener *mouseListener)
{
  itMouseListener = _mouseListeners.begin();
  itMouseListenerEnd = _mouseListeners.end();
  for (; itMouseListener != itMouseListenerEnd; ++itMouseListener) {
    if (itMouseListener->second == mouseListener) {
      _mouseListeners.erase(itMouseListener);
      break;
    }
  }
}

void
InputManager::removeAllListeners
()
{
  _keyListeners.clear();
  _mouseListeners.clear();
}

void
InputManager::removeAllKeyListeners ()
{
  _keyListeners.clear();
}

void
InputManager::removeAllMouseListeners ()
{
  _mouseListeners.clear();
}

void
InputManager::setWindowExtents
(int width, int height)
{
  // Establecer la región del ratón.
  // Llamar al hacer un resize.
  const OIS::MouseState &mouseState = _mouse->getMouseState();
  mouseState.width = width;
  mouseState.height = height;
}

OIS::Keyboard*
InputManager::getKeyboard ()
{
    return _keyboard;
}

OIS::Mouse*
InputManager::getMouse ()
{
    return _mouse;
}

bool
InputManager::keyPressed
(const OIS::KeyEvent &e)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(static_cast<CEGUI::Key::Scan>(e.key));
  CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(e.text);
  itKeyListener = _keyListeners.begin();
  itKeyListenerEnd = _keyListeners.end();
  // Delega en los KeyListener añadidos.
  for (; itKeyListener != itKeyListenerEnd; ++itKeyListener) {
    itKeyListener->second->keyPressed(e);
  }

  return true;
}

bool
InputManager::keyReleased
(const OIS::KeyEvent &e)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(static_cast<CEGUI::Key::Scan>(e.key));
  itKeyListener = _keyListeners.begin();
  itKeyListenerEnd = _keyListeners.end();
  // Delega en los KeyListener añadidos.
  for (; itKeyListener != itKeyListenerEnd; ++itKeyListener) {
    itKeyListener->second->keyReleased( e );
  }

  return true;
}

bool
InputManager::mouseMoved
(const OIS::MouseEvent &e)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(e.state.X.rel, e.state.Y.rel);
  itMouseListener = _mouseListeners.begin();
  itMouseListenerEnd = _mouseListeners.end();
 // Delega en los MouseListener añadidos.
  for (; itMouseListener != itMouseListenerEnd; ++itMouseListener) {
    itMouseListener->second->mouseMoved( e );
  }

  return true;
}

bool
InputManager::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertMouseButton(id));
  itMouseListener = _mouseListeners.begin();
  itMouseListenerEnd = _mouseListeners.end();
  // Delega en los MouseListener añadidos.
  for (; itMouseListener != itMouseListenerEnd; ++itMouseListener) {
    itMouseListener->second->mousePressed( e, id );
  }

    return true;
}

bool
InputManager::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertMouseButton(id));
  itMouseListener = _mouseListeners.begin();
  itMouseListenerEnd = _mouseListeners.end();
  // Delega en los MouseListener añadidos.
  for (; itMouseListener != itMouseListenerEnd; ++itMouseListener) {
    itMouseListener->second->mouseReleased( e, id );
  }

  return true;
}

CEGUI::MouseButton InputManager::convertMouseButton(OIS::MouseButtonID id)
{
  CEGUI::MouseButton ceguiId;
  switch(id)
    {
    case OIS::MB_Left:
      ceguiId = CEGUI::LeftButton;
      break;
    case OIS::MB_Right:
      ceguiId = CEGUI::RightButton;
      break;
    case OIS::MB_Middle:
      ceguiId = CEGUI::MiddleButton;
      break;
    default:
      ceguiId = CEGUI::LeftButton;
    }
  return ceguiId;
}

InputManager*
InputManager::getSingletonPtr ()
{
  return msSingleton;
}

InputManager&
InputManager::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

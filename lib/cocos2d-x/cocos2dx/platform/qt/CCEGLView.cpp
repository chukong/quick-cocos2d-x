/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCEGLView.h"
#include "cocoa/CCSet.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "text_input_node/CCIMEDispatcher.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"
#include "support/CCPointExtension.h"
#include "CCApplication.h"
#include "cocoa/CCInteger.h"

/// Qt
#include <QApplication>
#include <QDesktopWidget>
#include <QWindow>
#include <QTouchEvent>

#include <QOpenGLContext>
#include <QEvent>
#include <QMouseEvent>



#define USING_PROTOCOL_HANDLE 1

NS_CC_BEGIN


class Cocos2DQt5OpenGLIntegration : public QWindow {
    public:
        Cocos2DQt5OpenGLIntegration(int width, int height);
        ~Cocos2DQt5OpenGLIntegration();

//        virtual void touchEvent(QTouchEvent *event);
        virtual bool event(QEvent *event);

        void swapBuffers();

        // touch delegate
        typedef fastdelegate::FastDelegate1<QMouseEvent *> MyTouchDelegate;
        MyTouchDelegate touchMove;
        MyTouchDelegate touchBegin;
        MyTouchDelegate touchEnd;

        MyAccelerometerDelegate accelFunc;

    protected:
        virtual void mouseMoveEvent(QMouseEvent *event);
        virtual void mousePressEvent(QMouseEvent *event);
        virtual void mouseReleaseEvent(QMouseEvent *event);
        virtual void keyPressEvent(QKeyEvent *event);
        virtual void keyReleaseEvent(QKeyEvent *event);

    private:
        QOpenGLContext  *m_context;
};

Cocos2DQt5OpenGLIntegration::Cocos2DQt5OpenGLIntegration(int width, int height)
    : m_context(NULL)
{
    setSurfaceType(QSurface::OpenGLSurface);
    resize(width, height);

    // make this call: make opengl !!
    show();

    m_context = new QOpenGLContext(this);
    m_context->create();
    if (!m_context->makeCurrent(this)) {
        CCLOG(">> shit. makeCurrent failed!");
    }
}

Cocos2DQt5OpenGLIntegration::~Cocos2DQt5OpenGLIntegration()
{
    delete m_context;
}

#if 0
void
Cocos2DQt5OpenGLIntegration::touchEvent(QTouchEvent *event)
{
    Q_FOREACH (QTouchEvent::TouchPoint point, event->touchPoints()) {
        int id = point.id();
        QPointF pos = point.pos();
        float x = pos.x();
        float y = pos.y();
        Qt::TouchPointState state = point.state();

        switch (state) {
            case Qt::TouchPointPressed:
                m_egl_view->handleTouchesBegin(1, &id, &x, &y);
                break;
            case Qt::TouchPointMoved:
                m_egl_view->handleTouchesMove(1, &id, &x, &y);
                break;
            case Qt::TouchPointStationary:
                // Do nothing
                break;
            case Qt::TouchPointReleased:
                m_egl_view->handleTouchesEnd(1, &id, &x, &y);
                break;
            default:
                // Do nothing
                break;
        }
    }
    QWindow::touchEvent(event);
}
#endif

bool
Cocos2DQt5OpenGLIntegration::event(QEvent *event)
{
    if (event->type() == QEvent::Close) {
        CCDirector::sharedDirector()->end();
        delete m_context;
        m_context = NULL;
    }

    return QWindow::event(event);
}

void
Cocos2DQt5OpenGLIntegration::swapBuffers()
{
    if (m_context) {
        m_context->swapBuffers(this);
        m_context->makeCurrent(this);
    }
}

void Cocos2DQt5OpenGLIntegration::mousePressEvent(QMouseEvent *event)
{
    touchBegin(event);
    QWindow::mousePressEvent(event);
}

void Cocos2DQt5OpenGLIntegration::mouseMoveEvent(QMouseEvent *event)
{
    touchMove(event);
    QWindow::mouseMoveEvent(event);
}

void Cocos2DQt5OpenGLIntegration::mouseReleaseEvent(QMouseEvent *event)
{
    touchEnd(event);
    QWindow::mouseReleaseEvent(event);
}

void Cocos2DQt5OpenGLIntegration::keyPressEvent(QKeyEvent *event)
{
    if (accelFunc)
        accelFunc(event);
    QWindow::keyPressEvent(event);
}

void Cocos2DQt5OpenGLIntegration::keyReleaseEvent(QKeyEvent *event)
{
    if (accelFunc)
        accelFunc(event);
    QWindow::keyPressEvent(event);
}


////////////////////////////////// Cocos2DQt5OpenGLIntegration ////////////////////////////////////

static bool glew_dynamic_binding()
{
	const char *gl_extensions = (const char*)glGetString(GL_EXTENSIONS);

	// If the current opengl driver doesn't have framebuffers methods, check if an extension exists
	if (glGenFramebuffers == NULL)
	{
		CCLog("OpenGL: glGenFramebuffers is NULL, try to detect an extension\n");
		if (strstr(gl_extensions, "ARB_framebuffer_object"))
		{
			CCLog("OpenGL: ARB_framebuffer_object is supported\n");
#ifdef Q_OS_WIN_1
			glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) wglGetProcAddress("glIsRenderbuffer");
			glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) wglGetProcAddress("glBindRenderbuffer");
			glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) wglGetProcAddress("glDeleteRenderbuffers");
			glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) wglGetProcAddress("glGenRenderbuffers");
			glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) wglGetProcAddress("glRenderbufferStorage");
			glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetRenderbufferParameteriv");
			glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) wglGetProcAddress("glIsFramebuffer");
			glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebuffer");
			glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) wglGetProcAddress("glDeleteFramebuffers");
			glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffers");
			glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) wglGetProcAddress("glCheckFramebufferStatus");
			glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) wglGetProcAddress("glFramebufferTexture1D");
			glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2D");
			glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) wglGetProcAddress("glFramebufferTexture3D");
			glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) wglGetProcAddress("glFramebufferRenderbuffer");
			glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
			glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmap");
#else
#endif
		}
		else
		if (strstr(gl_extensions, "EXT_framebuffer_object"))
		{
			CCLog("OpenGL: EXT_framebuffer_object is supported\n");
#ifdef Q_OS_WIN_1
			glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) wglGetProcAddress("glIsRenderbufferEXT");
			glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) wglGetProcAddress("glBindRenderbufferEXT");
			glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) wglGetProcAddress("glDeleteRenderbuffersEXT");
			glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) wglGetProcAddress("glGenRenderbuffersEXT");
			glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) wglGetProcAddress("glRenderbufferStorageEXT");
			glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetRenderbufferParameterivEXT");
			glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) wglGetProcAddress("glIsFramebufferEXT");
			glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebufferEXT");
			glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) wglGetProcAddress("glDeleteFramebuffersEXT");
			glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffersEXT");
			glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) wglGetProcAddress("glCheckFramebufferStatusEXT");
			glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) wglGetProcAddress("glFramebufferTexture1DEXT");
			glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2DEXT");
			glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) wglGetProcAddress("glFramebufferTexture3DEXT");
			glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) wglGetProcAddress("glFramebufferRenderbufferEXT");
			glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) wglGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
			glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmapEXT");
#else

#endif
		}
		else
		{
			CCLog("OpenGL: No framebuffers extension is supported\n");
			CCLog("OpenGL: Any call to Fbo will crash!\n");
			return false;
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
// impliment CCEGLView
//////////////////////////////////////////////////////////////////////////
static CCEGLView* s_pMainWindow = NULL;

static void mouseMove(QMouseEvent *event)
{
    s_pMainWindow->mouseMove(event);
}

static void mousePress(QMouseEvent *event)
{
    s_pMainWindow->mousePress(event);
}

static void mouseRelease(QMouseEvent *event)
{
    s_pMainWindow->mouseRelease(event);
}

CCEGLView::CCEGLView()
    : m_bCaptured(false)
    , m_fFrameZoomFactor(1.0f)
    , m_bSupportTouch(false)
    , m_bIsInit(false)
    , m_fScreenScaleFactor(1.0f)
    , m_glParentWidget(NULL)
    , m_integration(NULL)
{
    m_pTouch = new CCTouch;
    m_pSet = new CCSet;
    strcpy(m_szViewName, "quick-cocos2d-x LuaHostWin32");
}

CCEGLView::~CCEGLView()
{
    CC_SAFE_DELETE(m_integration);
}

bool CCEGLView::initGL()
{
    // check OpenGL version at first
    const GLubyte* glVersion = glGetString(GL_VERSION);
    CCLog("OpenGL version = %s", glVersion);

    if ( glVersion && atof((const char*)glVersion) < 1.5 )
    {
        char strComplain[256] = {0};
        sprintf(strComplain,
        "OpenGL 1.5 or higher is required (your version is %s). Please upgrade the driver of your video card.",
        glVersion);
        CCMessageBox(strComplain, "OpenGL version too old");
        return false;
    }
#if USING_GLEW
    GLenum GlewInitResult = glewInit();
    if (GLEW_OK != GlewInitResult)
    {
		CCMessageBox((char *)glewGetErrorString(GlewInitResult), "OpenGL error");
        return false;
    }

    if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
    {
        CCLog("Ready for GLSL");
    }
    else
    {
        CCLog("Not totally ready :(");
    }

    if (glewIsSupported("GL_VERSION_2_0"))
    {
        CCLog("Ready for OpenGL 2.0");
    }
    else
    {
        CCLog("OpenGL 2.0 not supported");
    }

    if(glew_dynamic_binding() == false)
	{
		CCMessageBox("No OpenGL framebuffer support. Please upgrade the driver of your video card.", "OpenGL error");
		return false;
	}
#endif
    // Enable point size by default on windows.
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    return true;
}

void CCEGLView::destroyGL()
{
}

bool CCEGLView::Create()
{
    bool bRet = false;
    do
    {
        // Qt Window
        float iWidth = 320;
        float iHeight = 480;
#if 0
        m_glParentWidget = new QWidget();
        m_window = new GLWidget(iWidth, iHeight, m_glParentWidget);
        m_window->setAttribute(Qt::WA_DeleteOnClose);

        m_window->setMouseMoveFunc(&cocos2d::mouseMove);
        m_window->setMousePressFunc(&cocos2d::mousePress);
        m_window->setMouseReleaseFunc(&cocos2d::mouseRelease);

        m_window->setWindowFlags(m_window->windowFlags()& ~Qt::WindowMaximizeButtonHint);
        m_window->setFixedSize(iWidth, iHeight);

        // https://bugreports.qt-project.org/browse/QTBUG-8580
        m_window->hide();

        m_glParentWidget->show();

        // https://bugreports.qt-project.org/browse/QTBUG-8580
        m_window->show();

#else
        m_integration = new Cocos2DQt5OpenGLIntegration(iWidth, iHeight);
        m_integration->touchBegin.bind(this, &CCEGLView::mousePress);
        m_integration->touchMove.bind(this, &CCEGLView::mouseMove);
        m_integration->touchEnd.bind(this, &CCEGLView::mouseRelease);

        m_glParentWidget = QWidget::createWindowContainer(m_integration);
        m_glParentWidget->show();
#endif
        bRet = initGL();
        if(!bRet) destroyGL();
        CC_BREAK_IF(!bRet);

        m_bIsInit = true;
        s_pMainWindow = this;
        bRet = true;
    } while (0);

    return bRet;
}

bool CCEGLView::isOpenGLReady()
{
    return m_bIsInit;
}

void CCEGLView::end()
{
    // want here??
    m_bIsInit = false;
    CC_SAFE_DELETE(m_pSet);
    CC_SAFE_DELETE(m_pTouch);
    CC_SAFE_DELETE(m_glParentWidget);

    s_pMainWindow = NULL;

    qApp->exit(0);
}

void CCEGLView::swapBuffers()
{
    if (m_integration != NULL) {
        m_integration->swapBuffers();
    }
}


void CCEGLView::setIMEKeyboardState(bool /*bOpen*/)
{

}

void CCEGLView::setViewName(const char* pszViewName)
{
    CCEGLViewProtocol::setViewName(pszViewName);
    if (m_glParentWidget) {
        m_glParentWidget->setWindowTitle(getViewName());
    }
}

void CCEGLView::resize(int width, int height)
{
    do
    {
        m_glParentWidget->setFixedSize(width, height);
    } while(0);
}

void CCEGLView::setFrameZoomFactor(float fZoomFactor)
{
    m_fFrameZoomFactor = fZoomFactor;
    resize(m_obScreenSize.width * fZoomFactor, m_obScreenSize.height * fZoomFactor);
    centerWindow();
    CCDirector::sharedDirector()->setProjection(CCDirector::sharedDirector()->getProjection());
}

float CCEGLView::getFrameZoomFactor()
{
    return m_fFrameZoomFactor;
}

void CCEGLView::setFrameSize(float width, float height)
{
    CCEGLViewProtocol::setFrameSize(width, height);

    if (m_integration == NULL) {
        m_integration = new Cocos2DQt5OpenGLIntegration((int)width, (int)height);
    } else {
        m_integration->resize(width, height);
    }

    resize(width, height); // adjust window size for menubar
    centerWindow();
}

void CCEGLView::centerWindow()
{
    if (m_glParentWidget && !m_glParentWidget->parent()) {
        QDesktopWidget *w = qApp->desktop();
        QRect rect = w->screenGeometry();
        m_glParentWidget->move((rect.width()-m_glParentWidget->width())/2.0f
                              ,(rect.height()-m_glParentWidget->height())/2.0f);
    }
}

void CCEGLView::moveWindow(int left, int top)
{
    if (m_glParentWidget && !m_glParentWidget->parent()) {
        m_glParentWidget->move(left, top);
    }
}

void CCEGLView::setViewPortInPoints(float x , float y , float w , float h)
{
    glViewport((GLint)(x * m_fScaleX * m_fFrameZoomFactor + m_obViewPortRect.origin.x * m_fFrameZoomFactor),
        (GLint)(y * m_fScaleY  * m_fFrameZoomFactor + m_obViewPortRect.origin.y * m_fFrameZoomFactor),
        (GLsizei)(w * m_fScaleX * m_fFrameZoomFactor),
        (GLsizei)(h * m_fScaleY * m_fFrameZoomFactor));
}

void CCEGLView::setScissorInPoints(float x , float y , float w , float h)
{
    glScissor((GLint)(x * m_fScaleX * m_fFrameZoomFactor + m_obViewPortRect.origin.x * m_fFrameZoomFactor),
              (GLint)(y * m_fScaleY * m_fFrameZoomFactor + m_obViewPortRect.origin.y * m_fFrameZoomFactor),
              (GLsizei)(w * m_fScaleX * m_fFrameZoomFactor),
              (GLsizei)(h * m_fScaleY * m_fFrameZoomFactor));
}

CCEGLView* CCEGLView::sharedOpenGLView()
{
    if (s_pMainWindow == NULL)
    {
        CCEGLView *view = new CCEGLView();
		if(!view->Create())
		{
			delete view;
		}
    }

    return s_pMainWindow;
}

void CCEGLView::mouseMove(QMouseEvent *event)
{
    if (! m_pDelegate || ! m_pTouch)
        return;

    if (! m_bCaptured)
        return;

#if USING_PROTOCOL_HANDLE==1
    long wid = m_glParentWidget->winId();
    CCPoint pt(event->x(), event->y());
    pt.x /= m_fFrameZoomFactor;
    pt.y /= m_fFrameZoomFactor;

    CCEGLViewProtocol::handleTouchesMove(1, reinterpret_cast<int*>(&wid), &pt.x, &pt.y);

#else
    m_pTouch->setTouchInfo(0
                           , (float)(event->x()) / m_fScreenScaleFactor
                           , (float)(event->y()) / m_fScreenScaleFactor);
    m_pDelegate->touchesMoved(m_pSet, NULL);
#endif
}

void CCEGLView::mousePress(QMouseEvent *event)
{
    if (! m_pDelegate || ! m_pTouch)
        return;

    if (event->button() != Qt::LeftButton)
        return;

    m_bCaptured = true;

#if USING_PROTOCOL_HANDLE==1
    long wid = m_glParentWidget->winId();
    CCPoint pt(event->x(), event->y());
    pt.x /= m_fFrameZoomFactor;
    pt.y /= m_fFrameZoomFactor;

    CCEGLViewProtocol::handleTouchesBegin(1, reinterpret_cast<int*>(&wid), &pt.x, &pt.y);
#else
    m_pTouch->setTouchInfo(0,
                           (float)(event->x()) / m_fScreenScaleFactor,
                           (float)(event->y()) / m_fScreenScaleFactor);
    m_pSet->addObject(m_pTouch);
    m_pDelegate->touchesBegan(m_pSet, NULL);
#endif
}

void CCEGLView::mouseRelease(QMouseEvent *event)
{
    if (! m_pDelegate || ! m_pTouch)
        return;

    if (event->button() != Qt::LeftButton)
        return;

    m_bCaptured = false;

#if USING_PROTOCOL_HANDLE==1
    long wid = m_glParentWidget->winId();
    CCPoint pt(event->x(), event->y());
    pt.x /= m_fFrameZoomFactor;
    pt.y /= m_fFrameZoomFactor;

    CCEGLViewProtocol::handleTouchesEnd(1, reinterpret_cast<int*>(&wid), &pt.x, &pt.y);
#else
    m_pTouch->setTouchInfo(0,
                           (float)(event->x()) / m_fScreenScaleFactor,
                           (float)(event->y()) / m_fScreenScaleFactor);
    m_pDelegate->touchesEnded(m_pSet, NULL);
    m_pSet->removeObject(m_pTouch);
#endif
}

void CCEGLView::setAccelerometerKeyHook(MyAccelerometerDelegate accelerometerDelegate)
{
    if (m_integration) {
        m_integration->accelFunc = accelerometerDelegate;
    }
}

QWidget *CCEGLView::getGLWidget()
{
    return m_glParentWidget;
}

NS_CC_END

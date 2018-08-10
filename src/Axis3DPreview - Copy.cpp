#include "../include/Axis3DPreview.h"

Axis3DPreview::Axis3DPreview(QWidget *parent) :
    QOpenGLWidget(parent), m_program(nullptr)
{
    m_world.setToIdentity();
}

static const char *vertexShaderSource =
    "#version 150 core\n"
    "in vec3 in_Vertex;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 camera;\n"
    "uniform mat4 world;\n"
    "void main() {\n"
    "   gl_Position = projection * camera * world * vec4(in_Vertex, 1.0);\n"
    "}";

static const char *fragmentShaderSource =
    "#version 150 core\n"
    "in vec3 in_Color;\n"
    "out vec4 out_Color;\n"
    "void main() {\n"
    "   out_Color = vec4(in_Color, 1.0);"
    "}";

void Axis3DPreview::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &Axis3DPreview::cleanup);
    initializeOpenGLFunctions();

    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->bindAttributeLocation("in_Vertex", VERTEX);
    m_program->bindAttributeLocation("in_Color", COLOR);
    m_program->link();

    m_program->bind();
        m_uniformLocations.projection    = m_program->uniformLocation("projection");
        m_uniformLocations.world         = m_program->uniformLocation("world");
        m_uniformLocations.camera        = m_program->uniformLocation("camera");

        m_vao.create();

        m_vbo.create();
        m_vbo.bind();
            /* Sending datas to the GPU */
            m_vbo.allocate(m_vertices, 6 * sizeof(GLfloat)); // 6 vertices
            m_vbo.allocate(m_colors, 6 * sizeof(GLfloat));
        m_vbo.release();

        /* GPU sided code */
        QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao); // VAO binded

            m_vbo.bind();

                QOpenGLFunctions *f = context()->functions();
                f->glEnableVertexAttribArray(VERTEX);
                f->glEnableVertexAttribArray(COLOR);
                f->glVertexAttribPointer(VERTEX, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
                f->glVertexAttribPointer(COLOR, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));

            m_vbo.release();
        /* End of GPU sided code */

    m_program->release();

    /* Projection */
    m_perspective.setToIdentity();
    resizeGL(width(), height());

    /* Camera */
    m_camera.setToIdentity();
    m_camera.lookAt(QVector3D(2.0, 2.0, 2.0), QVector3D(0.0, 0.0, 0.0), QVector3D(0.0, 0.0, 1.0));
}

void Axis3DPreview::paintGL()
{
    qDebug() << "paintGL()";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* OpenGL */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao); // VAO binded
    m_program->bind();

        /* Draw here */
        m_program->setUniformValue(m_uniformLocations.projection, m_perspective);
        m_program->setUniformValue(m_uniformLocations.camera, m_camera);
        m_program->setUniformValue(m_uniformLocations.world, m_world);

        glDrawArrays(GL_LINES, 0, 6); // 6 vertices

    m_program->release();
}

void Axis3DPreview::resizeGL(int width, int height)
{
    m_perspective.setToIdentity();
    m_perspective.perspective(70.0, GLfloat(width) / height, 0.01f, 100.0f);
}

void Axis3DPreview::cleanup()
{
    if(m_program == nullptr) {
        return;
    }

    makeCurrent();
    m_vbo.destroy();
    delete m_program;
    m_program = 0;
    doneCurrent();
}

Axis3DPreview::~Axis3DPreview()
{
    cleanup();
}

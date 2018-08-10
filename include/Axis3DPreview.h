#ifndef AXIS3DPREVIEW_H
#define AXIS3DPREVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QtDebug>

#define VERTEX 0
#define COLOR  1

/* Defines a byte offset from an index offset */
#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + offset)
#endif

class Axis3DPreview : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

    public:
        Axis3DPreview(QWidget *parent = nullptr);
        virtual ~Axis3DPreview();

        void setRotation(double anglex, double angley, double anglez); // anglex is the rotation around the x-axis

    public slots:
        void cleanup();

    protected:
        void initializeGL() override;
        void paintGL() override;
        void resizeGL(int width, int height) override;

    private:
        /* Axis */
        const GLfloat m_vertices[18] = {0.0, 0.0, 0.0,      1.0, 0.0, 0.0,
                                        0.0, 0.0, 0.0,      0.0, 1.0, 0.0,
                                        0.0, 0.0, 0.0,      0.0, 0.0, 1.0};

        const GLfloat m_colors[18] =   {0.0, 0.0, 1.0,      0.0, 0.0, 1.0,
                                        0.0, 1.0, 0.0,      0.0, 1.0, 0.0,
                                        1.0, 0.0, 0.0,      1.0, 0.0, 0.0};

        /* World */
        QMatrix4x4  m_perspective,
                    m_world,
                    m_camera;

        /* OpenGL */
        QOpenGLVertexArrayObject    m_vao;
        QOpenGLBuffer               m_vbo;
        QOpenGLShaderProgram       *m_program;

        struct Locations {
            int projection,
                world,
                camera;
        } m_uniformLocations;
};

#endif // AXIS3DPREVIEW_H

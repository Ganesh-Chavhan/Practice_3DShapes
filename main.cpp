// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "openglwindow.h"
#include "shape.h"
#include "circle.h"     
#include "ellipse.h"
#include "cube.h"


#include <QGuiApplication>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QScreen>
#include <QtMath>

//! [1]
class TriangleWindow : public OpenGLWindow
{
public:
    using OpenGLWindow::OpenGLWindow;

    void initialize() override;
    void render() override;

private:
    GLint m_matrixUniform = 0;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram* m_program = nullptr;
    int m_frame = 0;
    int m_vertexCount = 0;         // ADDED

};
//! [1]

//! [2]
int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    TriangleWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

    window.setAnimating(true);

    return app.exec();
}
//! [2]

//! [3]
static const char* vertexShaderSource = "attribute highp vec4 posAttr;\n"
                                        "attribute lowp vec4 colAttr;\n"
                                        "varying lowp vec4 col;\n"
                                        "uniform highp mat4 matrix;\n"
                                        "void main() {\n"
                                        "   col = colAttr;\n"
                                        "   gl_Position = matrix * posAttr;\n"
                                        "}\n";

static const char* fragmentShaderSource = "varying lowp vec4 col;\n"
                                          "void main() {\n"
                                          "   gl_FragColor = col;\n"
                                          "}\n";
//! [3]

//! [4]
void TriangleWindow::initialize()
{
	//Shape *shape = new Circle(0.7f);
	Shape* shape = new Ellipse(0.5f, 0.3f);
	//Shape* shape = new Cube(0.5f);

    QVector<float> pts = shape->getPoints();
    m_vertexCount = pts.size() / 5; //for cube 6 and other 5  

    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(pts.data(), pts.size() * sizeof(float));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    // stride changed for cude
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
        reinterpret_cast<void*>(2 * sizeof(GLfloat)));

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->bindAttributeLocation("posAttr", 0);
    m_program->bindAttributeLocation("colAttr", 1);
    m_program->link();
    m_program->bind();

    m_matrixUniform = m_program->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
}
//! [4]

//! [5]
void TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    m_program->setUniformValue(m_matrixUniform, matrix);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //glDrawArrays(GL_LINE_LOOP, 0, m_vertexCount);
    glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertexCount);
	//glDrawArrays(GL_LINES, 0, m_vertexCount);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    m_program->release();

    ++m_frame;
}
//! [5]

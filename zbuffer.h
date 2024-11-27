#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <QLabel>
#include <QPainter>
#include <QVector3D>
#include <QColor>
#include <cmath>
#include <vector>
#include <tuple>
#include <algorithm>

class zbuffer : public QLabel
{
    Q_OBJECT

public:
    zbuffer(QWidget *parent = nullptr);

    QVector3D calculateCurve(double x, double y);
    QVector3D calculatePlane(double x, double y);

    QVector3D calculateCone(double t, double a);
    QVector3D calculateSphere(double a, double b);

    std::tuple<std::vector<QVector3D>, std::vector<QColor>> build_objects();
    void render_objects(QPainter &painter);
    void rotate_objects(double angleX, double angleY, double angleZ);

    void rotate_objects_Z(double angleZ);
    void rotate_objects_Y(double angleY);
    void rotate_objects_X(double angleX);

    void zbufferRender(const QSize &size, int offset); // Rename the function
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::tuple<std::vector<QVector3D>, std::vector<QColor>> objects;
    std::vector<std::vector<float>> zbuffer_;
    QTimer *rotationTimer;
    bool isRotating;
};

#endif // ZBUFFER_H

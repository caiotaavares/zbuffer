#include "zbuffer.h"

#include <QTimer>

zbuffer::zbuffer(QWidget *parent) : QLabel(parent), isRotating(false)
{
    objects = build_objects();
    zbufferRender(QSize(300, 300), 150);

    rotationTimer = new QTimer(this);
    connect(rotationTimer, &QTimer::timeout, this, [this]() {
        // Incrementos menores para rotação mais suave
        rotate_objects_X(0.1);    // Reduzir de 1.0 para 0.1
        rotate_objects_Y(0.1);
        rotate_objects_Z(0.1);
    });

    // Timer mais rápido para mais frames
    rotationTimer->setInterval(16);  // Aproximadamente 60 FPS
}

void zbuffer::zbufferRender(const QSize &size, int offset)
{
    int x = size.width();
    int y = size.height();

    // Configuração do zbuffer
    zbuffer_.resize(x, std::vector<float>(y, std::numeric_limits<float>::infinity()));

    // Atualize o widget para redesenhar
    update();
}

QVector3D zbuffer::calculateCurve(double x, double y)
{
    double z = (x * x + y) / 50.0; // Reduz o impacto do crescimento quadrático
    return QVector3D(x, y, z);
}

QVector3D zbuffer::calculatePlane(double x, double y)
{
    double z = (3 * x - 2 * y + 5) / 10.0; // Normalização simples
    return QVector3D(x, y, z);
}

QVector3D zbuffer::calculateCone(double t, double a)
{
    return QVector3D(30 + qCos(a) * t, 50 + qSin(a) * t, 10 + t);
}

QVector3D zbuffer::calculateSphere(double a, double b)
{
    return QVector3D(100 + 30 * qCos(a) * qCos(b), 50 + 30 * qCos(a) * qSin(b), 20 + 30 * qSin(a));
}

std::tuple<std::vector<QVector3D>, std::vector<QColor>> zbuffer::build_objects()
{
    std::vector<QVector3D> points;
    std::vector<QColor> colors;

    // Curva azul
    for (int x = 10; x <= 31; ++x)
    {
        for (int y = 20; y <= 41; ++y)
        {
            QVector3D point = calculateCurve(x, y);
            points.push_back(point);
            colors.push_back(QColor(0, 0, 255)); // Azul
        }
    }

    // Plano
    for (int x = 50; x <= 101; ++x)
    {
        for (int y = 30; y <= 81; ++y)
        {
            QVector3D point = calculatePlane(x, y);
            points.push_back(point);
            colors.push_back(QColor(255, 0, 0)); // Vermelho
        }
    }

    // Cone
    for (double a = 0; a < 4 * M_PI; a += 0.01)
    {
        for (int t = 0; t < 91; ++t)
        {
            QVector3D point = calculateCone(t, a);
            points.push_back(point);
            colors.push_back(QColor(255, 255, 0)); //Amare
        }
    }

    // Esfera
    for (double a = 0; a < 2 * M_PI; a += 0.01)
    {
        for (double b = 0; b < M_PI; b += 0.01)
        {
            QVector3D point = calculateSphere(a, b);
            points.push_back(point);
            colors.push_back(QColor(0, 255, 0));
        }
    }

    // Cubo
    for (int x = -20; x < 21; ++x)
    {
        for (int y = -20; y < 21; ++y)
        {
            points.push_back(QVector3D(x, y, -20));
            points.push_back(QVector3D(x, y, 20));
            points.push_back(QVector3D(x, 20, y));
            points.push_back(QVector3D(x, -20, y));
            points.push_back(QVector3D(20, x, y));
            points.push_back(QVector3D(-20, x, y));

            for (int i = 0; i < 6; ++i)
            {
                colors.push_back(QColor(255, 255, 255));
            }
        }
    }

    return std::make_tuple(points, colors);
}

void zbuffer::rotate_objects_X(double angleX)
{
    auto& [points, colors] = objects;

    const int xOffset = width() / 2;
    const int yOffset = height() / 2;

    double cosX = cos(angleX);
    double sinX = sin(angleX);

    for (QVector3D& point : points)
    {
        double oldY = point.y();
        double oldZ = point.z();

        // Apply rotation around the X-axis
        double newY = oldY * cosX - oldZ * sinX;
        double newZ = oldY * sinX + oldZ * cosX;
        point.setY(newY);
        point.setZ(newZ);
    }

    // Trigger a repaint
    update();
}

void zbuffer::rotate_objects_Y(double angleY)
{
    auto& [points, colors] = objects;

    const int xOffset = width() / 2;
    const int yOffset = height() / 2;

    double cosY = cos(angleY);
    double sinY = sin(angleY);

    for (QVector3D& point : points)
    {
        double oldX = point.x();
        double oldZ = point.z();

        // Apply rotation around the Y-axis
        double newX = oldX * cosY + oldZ * sinY;
        double newZ = -oldX * sinY + oldZ * cosY;
        point.setX(newX);
        point.setZ(newZ);
    }

    // Trigger a repaint
    update();
}

void zbuffer::rotate_objects_Z(double angleZ)
{
    auto& [points, colors] = objects;

    const int xOffset = width() / 2;
    const int yOffset = height() / 2;

    double cosZ = cos(angleZ);
    double sinZ = sin(angleZ);

    for (QVector3D& point : points)
    {
        double oldX = point.x();
        double oldY = point.y();

        // Apply rotation around the Z-axis
        double newX = oldX * cosZ - oldY * sinZ;
        double newY = oldX * sinZ + oldY * cosZ;
        point.setX(newX);
        point.setY(newY);
    }

    // Trigger a repaint
    update();
}

void zbuffer::rotate_objects(double anglex, double angley, double anglez)
{
    if (!isRotating) {
        rotationTimer->start();  // Inicia o timer
        isRotating = true;
    } else {
        rotationTimer->stop();  // Para o timer
        isRotating = false;
    }
}

void zbuffer::render_objects(QPainter &painter)
{
    auto [points, colors] = objects;

    const int xOffset = width() / 2;
    const int yOffset = height() / 2;

    // Ordena os pontos com base na coordenada Z
    std::vector<int> indices(points.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::sort(indices.begin(), indices.end(), [&](int a, int b) {
        return points[a].z() < points[b].z();
    });

    for (int i : indices)
    {
        // Configura a cor
        painter.setPen(colors[i]);

        // Desenha o ponto
        painter.drawPoint(points[i].x() + xOffset, points[i].y() + yOffset);
    }
}

void zbuffer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    // Chama a função de renderização
    render_objects(painter);
}

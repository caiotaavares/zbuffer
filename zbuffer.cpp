#include "zbuffer.h"

zbuffer::zbuffer(QWidget *parent) : QLabel(parent)
{
    objects = build_objects();
    zbufferRender(QSize(300, 300), 150);  // Use the correct function name
}

void zbuffer::zbufferRender(const QSize &size, int offset)
{
    int x = size.width();
    int y = size.height();

    zbuffer_.resize(x, std::vector<float>(y, std::numeric_limits<float>::infinity()));

    // Reuse the QPainter and batch painting operations
    QPainter painter(this);
    render_objects(painter);

    // Trigger a repaint
    update();
}

double zbuffer::calculateAzul(double x, double y)
{
    return x * x + y;
}

double zbuffer::calculateVermelho(double x, double y)
{
    return 3 * x - 2 * y + 5;
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

    // Cone
    for (double a = 0; a < 4 * M_PI; a += 0.01)
    {
        for (int t = 0; t < 91; ++t)
        {
            QVector3D point = calculateCone(t, a);
            points.push_back(point);
            colors.push_back(QColor(255, 0, 0));
        }
    }

    // Sphere
    for (double a = 0; a < 4 * M_PI; a += 0.01)
    {
        for (double b = 0; b < 4 * M_PI; b += 0.01)
        {
            QVector3D point = calculateSphere(a, b);
            points.push_back(point);
            colors.push_back(QColor(255, 0, 255));
        }
    }

    // Cube
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
                colors.push_back(QColor(255, 200, 55));
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

void zbuffer::render_objects(QPainter &painter)
{
    auto [points, colors] = objects;

    const int xOffset = width() / 2;
    const int yOffset = height() / 2;

    // Create a vector of indices and sort them based on the Z-coordinate
    std::vector<int> indices(points.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::sort(indices.begin(), indices.end(), [&](int a, int b) {
        return points[a].z() < points[b].z();
    });

    // Begin the painting operations
    painter.begin(this);

    for (int i : indices)
    {
        // Set pen color
        painter.setPen(colors[i]);

        // Draw point
        painter.drawPoint(points[i].x() + xOffset, points[i].y() + yOffset);
    }

    // End the painting operations
    painter.end();
}

void zbuffer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    render_objects(painter);
}

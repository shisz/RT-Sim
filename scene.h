#ifndef SCENE_H
#define SCENE_H

#include <QObject>

#include <QImage>
#include <QPainter>

#include <geobase.h>

#include <omp.h>
#include <iostream>

class Scene : public QObject {
  Q_OBJECT
 public:
  explicit Scene(QObject *parent = nullptr);

  std::vector<LineSeg> line_list;  // scene

  std::vector<Point> beacon_list;  // valid beacons

  std::vector<Point> tra_list;  // valid trajectory

  bool loadDefult() {
    line_list.push_back(LineSeg(Point(0, 0), Vector(10, 0)));
    line_list.push_back(LineSeg(Point(0, 0), Vector(0, 10)));
    line_list.push_back(LineSeg(Point(10, 0), Vector(0, 10)));
    line_list.push_back(LineSeg(Point(0, 10), Vector(10, 0)));
    line_list.push_back(LineSeg(Point(5, 2), Vector(0, 6)));
    line_list.push_back(LineSeg(Point(3, 6), Vector(0, -3)));
    line_list.push_back(LineSeg(Point(5, 7), Vector(-3, 0)));
    line_list.push_back(LineSeg(Point(5, 3), Vector(3, 0)));
    line_list.push_back(LineSeg(Point(7, 4), Vector(0, 3)));

    drawScene();
    return true;
  }

  /**
   * @brief loadScene
   * @param s_str
   *  each line of string represented a line segment in the scene.
   * format:
   * start_point_x,start_point_y,ori_vec_x,ori_vec_y
   * @return
   */
  bool loadScene(const QString s_str);

  /**
   * @brief loadBeacon
   * @param b_str
   * each line of string represented a beacon
   * beacon_x, beacon_y
   * @return
   */
  bool loadBeacon(const QString b_str);

  /**
   * @brief loadTrajectory
   * @param t_str
   * @return
   */
  bool loadTrajectory(const QString t_str);

  /**
   * @brief drawScene
   * draw the scene, including scene, beacon, trajectory, current pose, current
   * ray tracing result.
   * @return
   */
  bool drawScene();

  /**
   * @brief initalAxis
   * initial axis based on line segment !!! WARNING.
   * @return
   */
  bool initalAxis();

  /**
   * @brief toImage
   * @param v in image frame
   * @return
   */
  Vector toImage(const Vector &v);
  /**
   * @brief toImage
   * @param v in image frame
   * @return
   */
  Point toImage(const Point &v);

  // transform parameters
  double img_height = 1000;
  double img_width = 1000;
  double x_scale = 100.0;
  double y_scale = 100.0;
  double x_offset = 0;
  double y_offset = 0;

 signals:
  void newImage(QImage img);

 public slots:
};

#endif  // SCENE_H

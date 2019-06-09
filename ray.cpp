#include "ray.h"

double Ray::detect_intersection(const LineSeg &l, Point &intersect_point) {
  double a(cur_vec.x * -1.0);
  double b(l.ori_vec.x);
  double c(cur_vec.y * -1.0);
  double d(l.ori_vec.y);

  double Adet = a * d - b * c;
  if (std::abs(Adet) > 0.0) {
    double Astar = 1.0 / Adet;

    double inv_a(Astar * d);
    double inv_b(Astar * -1.0 * b);
    double inv_c(Astar * -1.0 * c);
    double inv_d(Astar * a);

    double g1 = cur_point.x - l.start_point.x;
    double g2 = cur_point.y - l.start_point.y;

    double ray_fac = inv_a * g1 + inv_b * g2;
    double line_fac = inv_c * g1 + inv_d * g2;

    if (ray_fac >= 0.0 && line_fac >= 0.0 && line_fac <= 1.0) {
      Point p_ray(cur_point.x + cur_vec.x * ray_fac,
                  cur_point.y + cur_vec.y * ray_fac);

      // cur_point + cur_vec * ray_fac;
      Point p_line(l.start_point.x + l.ori_vec.x * line_fac,
                   l.start_point.y + l.ori_vec.y * line_fac);
      if (p_ray.isClose(p_line)) {
        intersect_point.x = p_ray.x;
        intersect_point.y = p_ray.y;
        return cur_vec.len() * ray_fac;
      } else {
        std::cout << "there are some error:"
                  << "p ray :" << p_ray.x << "," << p_ray.y
                  << "p line:" << p_line.x << "," << p_line.y << std::endl;
        return -1.0;
      }
    } else {
      return -1.0;
    }

  } else {
    return -1.0;
  }
  std::cout << "l:" << l.start_point.x << "," << l.start_point.y
            << " l v:" << l.ori_vec.x << "," << l.ori_vec.y << std::endl;
  std::cout << "cur p:" << cur_point.x << "," << cur_point.y
            << " cur vec:" << cur_vec.x << "," << cur_vec.y << std::endl;
  std::cout << "Adet:" << Adet << std::endl;

  return -1.0;
}

bool Ray::reflection(Point p, Vector norm_vec) {
  if (cur_vec.cos(norm_vec) < 0.0) {
    norm_vec.x *= -1.0;
    norm_vec.y *= -1.0;
  }
  if (norm_vec.len() < EPS) {
    std::cout << "som error of reflection using error norm vector:"
              << std::endl;
  }

  double idotn2 = (norm_vec.x * cur_vec.x + norm_vec.y * cur_vec.y);
  double x = cur_vec.x;
  double y = cur_vec.y;
  if (std::abs(idotn2) < EPS) {
    std::cout << "some error of idotn2:" << idotn2 << std::endl;
  }

  LineSeg l_ray(Point(cur_point.x, cur_point.y),
                Vector(p.x - cur_point.x, p.y - cur_point.y));
  line_list.push_back(l_ray);

  Vector reflec_vec(x - idotn2 * norm_vec.x * 2.0,
                    y - idotn2 * norm_vec.y * 2.0);

  cur_vec = Vector(reflec_vec.x, reflec_vec.y);
  cur_point = Point(p.x, p.y);

  return true;
}

bool Ray::reachedPoint(Point p, double max_dis) {
  if (max_dis < 0.0) {
    std::cout << "some error  max dis::" << max_dis << std::endl;
  }
  Vector pv_vec = Vector(p.x - cur_point.x, p.y - cur_point.y);
  double cos_theta = pv_vec.cos(cur_vec);
  if (sqrt(1.0 - cos_theta * cos_theta) * pv_vec.len() < 0.05 &&
      pv_vec.len() < max_dis &&
      cos_theta > 0.9) {  // && std::abs(cos_theta) < M_PI / 4.0) {
    line_list.push_back(
        LineSeg(cur_point, Vector(p.x - cur_point.x, p.y - cur_point.y)));
    reached_flag = true;
    return true;
  } else {
    return false;
  }
}

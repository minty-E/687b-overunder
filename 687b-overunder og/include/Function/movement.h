using namespace vex;

class Function {
  public:
    static void driveControl();
    static void setVel(double AxisOne, double AxisTwo);
    static void setStop(brakeType type);
};
#include <ignition/math/Pose3.hh>
#include "gazebo/physics/physics.hh"
#include "gazebo/common/common.hh"
#include "gazebo/gazebo.hh"

namespace gazebo
{
class Roombamodel : public WorldPlugin
	{
		public: void Load(physics::WorldPtr _parent, sdf::ElementPtr /*_sdf*/)
			{
				_parent->InsertModelFile("model://roomba1");
			}
	};

GZ_REGISTER_WORLD_PLUGIN(Roombamodel)
}
			


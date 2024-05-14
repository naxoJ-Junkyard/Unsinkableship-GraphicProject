
#include <iostream>
#include <memory>
#include <glad/glad.h>

#include "Mesh3D.h"
#include "Object3D.h"
#include "AssimpImport.h"
#include "Animator.h"
#include "ShaderProgram.h"

#include <cstdlib> 
#include <ctime>
#include "TranslationAnimation.h"
#include "RotationAnimation.h"
#include "PauseAnimation.h"
#include "BezierAnimation.h"

struct Scene {
	ShaderProgram defaultShader;
	std::vector<Object3D> objects;
	std::vector<Animator> animators;
};

ShaderProgram phongLighting() {
	ShaderProgram program;
	try {
		program.load("shaders/light_perspective.vert", "shaders/lighting.frag");
	}
	catch (std::runtime_error& e) {
		std::cout << "ERROR: " << e.what() << std::endl;
		exit(1);
	}
	return program;
}

ShaderProgram textureMapping() {
	ShaderProgram program;
	try {
		program.load("shaders/texture_perspective.vert", "shaders/texturing.frag");
	}
	catch (std::runtime_error& e) {
		std::cout << "ERROR: " << e.what() << std::endl;
		exit(1);
	}
	return program;
}


Texture loadTexture(const std::filesystem::path& path, const std::string& samplerName = "baseTexture") {
	sf::Image i;
	i.loadFromFile(path.string());
	return Texture::loadImage(i, samplerName);
}


Scene marbleSquare() {
	std::vector<Texture> textures = {
		loadTexture("models/White_marble_03/Textures_4K/white_marble_03_4k_baseColor.tga", "baseTexture"),
	};

	auto mesh = Mesh3D::square(textures);
	auto square = Object3D(std::vector<Mesh3D>{mesh});
	square.grow(glm::vec3(5, 5, 5));
	square.rotate(glm::vec3(-3.14159 / 4, 0, 0));

	std::vector<Object3D> objects;
	objects.push_back(std::move(square));
	return Scene{
		phongLighting(),
		//textureMapping(),
		std::move(objects)
	};
}


Scene bunny() {
	auto bunny = assimpLoad("models/bunny/bunny_textured.obj", true);
	bunny.move(glm::vec3(0.2, -1, -1));
	bunny.grow(glm::vec3(9, 9, 9));
	bunny.setVelocity(glm::vec3(2.0, 10.0, 0.0));
	bunny.setMass(1.0);

	std::vector<Texture> textures = {
		loadTexture("models/White_marble_03/Textures_4K/white_marble_03_4k_baseColor.tga", "baseTexture"),
	};

	auto mesh = Mesh3D::square(textures);
	auto square = Object3D(std::vector<Mesh3D>{mesh});
	square.grow(glm::vec3(5, 5, 5));
	square.rotate(glm::vec3(-3.14159 / 4, 0, 0));
	square.setVelocity(glm::vec3(2.0, 10.0, 0.0));
	square.setMass(1.0);


	std::vector<Object3D> objects;
	objects.push_back(std::move(bunny));
	objects.push_back(std::move(square));
	return Scene{
		//phongLighting(),
		textureMapping(),
		std::move(objects)
	};
}



static Scene UnsinkableShip() {
	auto bottle = assimpLoad("models/bottle/Vintage-Bottle_OBJ.obj", true);
	bottle.grow(glm::vec3(.5, .5, .5));
	bottle.move(glm::vec3(0.2, -1, 0));
	bottle.setVelocity(glm::vec3(5.0, 5.0, 0.0));
	bottle.setMass(1.0);

	//auto tugboat = assimpLoad("models/tug_boat_v2/tug_boat_v2.obj", true);
	//tugboat.grow(glm::vec3(0.005, 0.005, 0.005));
	//tugboat.rotate(glm::vec3(-1.2, 0.0, 0.0));
	//tugboat.move(glm::vec3(0.0, .0, 30.0));



	auto shipwithsails = assimpLoad("models/ship_with_sails/ship.obj", true);
	shipwithsails.grow(glm::vec3(0.07, 0.07, 0.07));
	shipwithsails.move(glm::vec3(0, 0, 20));
	shipwithsails.rotate(glm::vec3(0, 1.5, 0));
	//bottle.addChild(std::move(shipwithsails));

	shipwithsails.setVelocity(glm::vec3(0.0, 5.0, 0.0));
	//shipwithsails.setAcceleration(glm::vec3(0.0f, -9.8, 0.0));
	//shipwithsails.setRotationalAcceleration(glm::vec3(0.0, 0.1, 0.0));
	shipwithsails.setMass(1.2);
	//shipwithsails.applyForce(glm::vec3(0.0, -9.8, 0.0));


	//std::vector<Texture> textures = {
	//	loadTexture("models/White_marble_03/Textures_4K/white_marble_03_4k_baseColor.tga", "baseTexture"),
	//};

	//auto mesh = Mesh3D::square(textures);
	//auto square = Object3D(std::vector<Mesh3D>{mesh});
	//square.grow(glm::vec3(5, 5, 5));
	//square.rotate(glm::vec3(-3.14159 / 4, 0, 0));
	
	//shipwithsails.addChild(square);

	std::vector<Object3D> objects;
	//objects.push_back(std::move(bottle));
	//objects.push_back(std::move(pirateship));
	//objects.push_back(std::move(tugboat)); //shows
	objects.push_back(std::move(shipwithsails)); //shows
	//objects.push_back(std::move(balls));

	//objects.push_back(std::move(bottle));



	Animator animBoat;
	//animBoat.addAnimation(std::make_unique<RotationAnimation>(objects[1], 5, glm::vec3(0, 6.28, 0)));
	std::vector<Animator> animators;
	animators.push_back(std::move(animBoat));

	return Scene{
		//textureMapping(),
		phongLighting(),
		std::move(objects),
		std::move(animators)

	};

}

static Scene Ocean() {
	std::vector<Texture> textures = {
		loadTexture("models/ocean/ocean2.jpg", "baseTexture"),
	};
	std::vector<Texture> skytextop = {
		loadTexture("models/ocean/skysun1.jpg", "baseTexture"),
	};
	std::vector<Texture> skytexsides = {
		loadTexture("models/ocean/sky3.jpg", "baseTexture"),
	};

	auto skytop = Mesh3D::square(skytextop);
	auto skysides = Mesh3D::square(skytexsides);
	auto mesh = Mesh3D::square(textures);
	auto boxTop = Object3D(std::vector<Mesh3D>{skytop});
	auto boxBottom = Object3D(std::vector<Mesh3D>{mesh});
	auto boxFront = Object3D(std::vector<Mesh3D>{mesh});
	auto boxBack = Object3D(std::vector<Mesh3D>{skysides});
	auto boxLeft = Object3D(std::vector<Mesh3D>{skysides});
	auto boxRight = Object3D(std::vector<Mesh3D>{skysides});

	
	float growAmount = 40.0;
	float halfBoxSize = growAmount / 2.0;

	//form a box
	boxTop.move(glm::vec3(0, halfBoxSize, 0));
	boxBottom.move(glm::vec3(0, -halfBoxSize, 0));
	boxFront.move(glm::vec3(0, -halfBoxSize*2, halfBoxSize));
	boxBack.move(glm::vec3(0, 0, -halfBoxSize));
	boxLeft.move(glm::vec3(-halfBoxSize, 0, 0));
	boxRight.move(glm::vec3(halfBoxSize, 0, 0));

	boxTop.rotate(glm::vec3(glm::radians(90.0), 0, 0));
	boxBottom.rotate(glm::vec3(glm::radians(90.0), 0, 0));
	boxFront.rotate(glm::vec3(0, glm::radians(0.0), 0));
	boxBack.rotate(glm::vec3(0, glm::radians(0.0), 0));
	boxLeft.rotate(glm::vec3(0, glm::radians(-90.0), 0));
	boxRight.rotate(glm::vec3(0, glm::radians(90.0), 0));


	std::vector<Object3D> objects;
	objects.push_back(std::move(boxTop));
	objects.push_back(std::move(boxBottom));
	objects.push_back(std::move(boxFront));
	objects.push_back(std::move(boxBack));
	objects.push_back(std::move(boxLeft));
	objects.push_back(std::move(boxRight));

	for (auto& o : objects){
		o.grow(glm::vec3(growAmount, growAmount, growAmount));
		o.move(glm::vec3(0, 0, 20));
		o.setCenter(glm::vec3(0,0,0));
	}

	

	return Scene{
		//textureMapping(),
		phongLighting(),
		std::move(objects),

	};
}


// Function to generate a random float between min and max
static float randomFloat(float min, float max) {
	return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
}
static Scene OceanBalls() {


	std::vector<Object3D> objects;
	//auto ballModel = assimpLoad("models/sphere/3d-model.obj", true);
	//ballModel.grow(glm::vec3(0.05, 0.05, 0.05));

	auto ballModel = assimpLoad("models/sphere/Blueberry.obj", true);
	ballModel.grow(glm::vec3(700, 700, 700));

	//ballModel.setVelocity(glm::vec3(0.0, 0.0, 0.0));
	ballModel.setMass(1.0);


	for (int i = 0; i < 75; ++i) {
		auto ball = ballModel;

		// random positions
		float ranX = randomFloat(-20.0, 20.0);
		float ranY = randomFloat(-20.0, 0.0);
		float ranZ = randomFloat(0.0, 30.0);

		ball.setPosition(glm::vec3(ranX, ranY, ranZ));

		// random velocities
		float ranXvel = randomFloat(-3.0, 3.0);
		float ranYvel = randomFloat(-2.0, 2.0);
		float ranZvel = randomFloat(-1.0, 1.0);

		ball.setVelocity(glm::vec3(ranXvel, ranYvel, ranZvel));

		ball.rotate(glm::vec3(3.14159, 0, 0));
		objects.push_back(std::move(ball));
	}

	
	return Scene{
		//textureMapping(),
		phongLighting(),
		std::move(objects)
	};

}

Scene Birds() {
	std::vector<Object3D> objects;

	auto bird = assimpLoad("models/bird/jet_by_dommk.obj", true);
	bird.grow(glm::vec3(.005,.005,.005));
	bird.move(glm::vec3(0, -0.5, -5.5));
	bird.rotate(glm::vec3(0, glm::radians(-90.0), 0));

	//bird.move(glm::vec3(30,0,7));
	//bird.setVelocity(glm::vec3(1.0, 1.0, 0.0));
	//bird.setMass(1.0);

	auto fire = assimpLoad("models/bird/fire/campfire.obj", true);
	fire.grow(glm::vec3(1,1,1));
	fire.rotate(glm::vec3(0,glm::radians(90.0),0));
	fire.move(glm::vec3(30, 0, 7));

	fire.addChild(std::move(bird));

	//objects.push_back(std::move(bird));
	objects.push_back(std::move(fire));

	Animator anim;

	anim.addAnimation(std::make_unique<RotationAnimation>(objects[0], 1, glm::vec3(glm::radians(30.0), 0, 0)));
	for (int i = 0; i < 2; ++i) {
		//left
		anim.addAnimation(std::make_unique<PauseAnimation>(objects[0], 6));
		anim.addAnimation(std::make_unique<BezierAnimation>(objects[0], 11, glm::vec3(30, 0, 7), glm::vec3(-7, -7, 30), glm::vec3(-10, 15, -5), glm::vec3(-35, 2, 7)));
		anim.addAnimation(std::make_unique<RotationAnimation>(objects[0], 1, glm::vec3(0, glm::radians(180.0), 0)));
		//right
		anim.addAnimation(std::make_unique<PauseAnimation>(objects[0], 6));
		anim.addAnimation(std::make_unique<BezierAnimation>(objects[0], 11, glm::vec3(-35, 2, 7), glm::vec3(-10, 15, -5), glm::vec3(-7, -7, 30), glm::vec3(30, 0, 7)));
		anim.addAnimation(std::make_unique<RotationAnimation>(objects[0], 1, glm::vec3(0, glm::radians(180.0), 0)));
	}
	//end it all
	anim.addAnimation(std::make_unique<PauseAnimation>(objects[0], 5));
	anim.addAnimation(std::make_unique<RotationAnimation>(objects[0], 1, glm::vec3(glm::radians(30.0), 0, glm::radians(30.0))));
	anim.addAnimation(std::make_unique<TranslationAnimation>(objects[0], 2.5, glm::vec3(-45, -20, 30)));
	//anim.addAnimation(std::make_unique<RotationAnimation>(objects[0], 1, glm::vec3(0, glm::radians(180.0), 0)));
	//anim.addAnimation(std::make_unique<PauseAnimation>(objects[0], 5));
	std::vector<Animator> animators;
	animators.push_back(std::move(anim));
	return Scene{
		//textureMapping(),
		phongLighting(),
		std::move(objects),
		std::move(animators)
	};
}


int main() {
	// Initialize the window and OpenGL.
	sf::ContextSettings Settings;
	Settings.depthBits = 24; // Request a 24 bits depth buffer
	Settings.stencilBits = 8;  // Request a 8 bits stencil buffer
	Settings.antialiasingLevel = 2;  // Request 2 levels of antialiasing
	sf::RenderWindow window(sf::VideoMode{ 1200, 800 }, "SFML Demo", sf::Style::Resize | sf::Style::Close, Settings);
	auto windowSize = window.getSize();
	gladLoadGL();
	glEnable(GL_DEPTH_TEST);


	// Initialize scene objects.
	auto scene = UnsinkableShip();
	auto ocean = Ocean();
	auto balls = OceanBalls();
	auto birds = Birds();
	//auto scene = lifeOfPi();

	//ocean bounds
	double oMinX=100.0, oMinY= 100.0, oMinZ=100.0, oMaxX= -100.0, oMaxY = -100.0, oMaxZ = -100.0;
	glm::vec3 oMin(0, 0, 0);
	glm::vec3 oMax(0, 0, 0);
	for (auto& o : ocean.objects) {
		if (o.getPosition().x < oMinX) {
			oMinX = o.getPosition().x;
		}
		if (o.getPosition().y < oMinY) {
			oMinY = o.getPosition().y;
		}
		if (o.getPosition().z < oMinZ) {
			oMinZ = o.getPosition().x;
		}
		if (o.getPosition().x > oMaxX) {
			oMaxX = o.getPosition().x;
		}
		if (o.getPosition().y > oMaxY) {
			oMaxY = o.getPosition().y;
		}
		if (o.getPosition().z > oMaxZ) {
			oMaxZ = o.getPosition().z;
		}
		
	}
	oMin = glm::vec3(oMinX, oMinY, oMinZ);
	oMax = glm::vec3(oMaxX, oMaxY, oMaxZ);
	//std::cout << "min " << oMin.x<<oMin.y<<oMin.z << " max " << oMax.x<<oMax.y<<oMax.z;



	srand(time(nullptr));



	// In case you want to manipulate the scene objects directly by name.
	//auto& boat = scene.objects[0];
	//auto& tiger = boat.getChild(1);

	//glm::vec3 velocity = scene.objects[0].getVelocity();
	//glm::vec3 acceleration = scene.objects[0].getAcceleration();


	auto cameraPosition = glm::vec3(0, 0, 70);
	auto camera = glm::lookAt(cameraPosition, glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	auto perspective = glm::perspective(glm::radians(45.0), static_cast<double>(window.getSize().x) / window.getSize().y, 0.1, 100.0);
	float yawAngle = 0.0;
	float rollAngle = 0.0;

	ShaderProgram& mainShader = scene.defaultShader;
	mainShader.activate();
	mainShader.setUniform("view", camera);
	mainShader.setUniform("projection", perspective);

	ShaderProgram& boatShader = scene.defaultShader;
	boatShader.activate();
	boatShader.setUniform("view", camera);
	boatShader.setUniform("projection", perspective);


	glm::vec4 materialParams(2.0, 1.0, 0.5, 10.0);
	boatShader.setUniform("material", materialParams); //k_a, k_d, k_s, and shininess

	glm::vec3 ambientColor(0.2, 0.2, 0.2); // rgb dark gray ambient light
	boatShader.setUniform("ambientColor", ambientColor);

	glm::vec3 directionalLight(5, -5, -5);
	glm::vec3 directionalColor(1.0, 1.0, 1.0); //rgb white directional light
	boatShader.setUniform("directionalLight", directionalLight);
	boatShader.setUniform("directionalColor", directionalColor);


	


	// Ready, set, go!
	for (auto& animator : birds.animators) {
		animator.start();
	}
	bool running = true;
	sf::Clock c;
	auto last = c.getElapsedTime();
	while (running) {
		sf::Event ev;
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				running = false;
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (yawAngle < 0.4) {
				yawAngle += 0.001;
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (yawAngle > -0.4) {
				yawAngle -= 0.001;
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (rollAngle < 0.2){
				rollAngle += 0.001;
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (rollAngle > -0.2) {
				rollAngle -= 0.001;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			rollAngle = 0.0;
			yawAngle = 0.0;
			
			for (auto& o : scene.objects) {
				o.setPosition(glm::vec3(0, 0, 20));
				o.setVelocity(glm::vec3(0, 0, 0));
			}
			
			for (auto& ball : balls.objects) {
				// random positions
				float ranX = randomFloat(-20.0, 20.0);
				float ranY = randomFloat(-20.0, -5.0);
				float ranZ = randomFloat(0.0, 30.0);
				ball.setPosition(glm::vec3(ranX, ranY, ranZ));

				// random velocities
				float ranXvel = randomFloat(-3.0, 3.0);
				float ranYvel = randomFloat(-2.0, 2.0);
				float ranZvel = randomFloat(-1.0, 1.0);
				ball.setVelocity(glm::vec3(ranXvel, ranYvel, ranZvel));
			}
			//balls = OceanBalls();
			birds = Birds();
			for (auto& animator : birds.animators) {
				animator.start();
			}
			
			
		}
		//update camera
		auto yawRotation = glm::rotate(glm::mat4(1.0), yawAngle, glm::vec3(0, 0, 1));
		auto rollRotation = glm::rotate(glm::mat4(1.0), rollAngle, glm::vec3(1, 0, 0));
		auto cameraRotation = yawRotation * rollRotation;
		auto cameraView = glm::lookAt(cameraPosition, glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
		auto camera = cameraView * cameraRotation;
		mainShader.setUniform("view", camera);
		boatShader.setUniform("view", camera);
		
		
		//std::cout << "Camera rotation matrix: " << std::endl;
		//for (int i = 0; i < 4; ++i) {
			//for (int j = 0; j < 4; ++j) {
				//std::cout << cameraRotation[i][j] << " ";
			//}
			//std::cout << std::endl;
		//}

		auto now = c.getElapsedTime();
		auto diff = now - last;
		auto diffSeconds = diff.asSeconds();
		last = now;
		
		//simulation
		for (auto& o : scene.objects) {
			//put gravity in camera space
			auto inverseCam = glm::inverse(cameraRotation);
			auto gravityInCam = glm::vec3(inverseCam * glm::vec4(0.0, -9.8, 0.0, 0.0));


			o.applyForce(gravityInCam);
			//o.applyForce(glm::vec3(0.0, -9.8, 0.0));
			glm::vec3 velocity = o.getVelocity();
			glm::vec3 acceleration = o.getAcceleration();
			auto objPosition = o.getPosition();
			auto objScale = o.getScale();
			auto objSize = glm::vec3(5, 4.4, 2.1); //x and y valuses| there has to be a way to get the bounds of the object
			//std::cout << "Object position: " << objPosition.x << ", " << objPosition.y << std::endl;
			//std::cout << "Object velocity: " << velocity.x << ", " << velocity.y << std::endl;
			//std::cout << "Object acceleration: " << acceleration.x << ", " << acceleration.y << std::endl;

			glm::vec3 accelerationDirection = glm::normalize(acceleration);

			// calculate angles for the boat
			float yaw = atan2(accelerationDirection.z, accelerationDirection.x);
			//float yaw = atan2(yaww, accelerationDirection.y);
			//keep within 0 to 2 pi
			yaw = fmod(yaw + 2 * 3.14159, 2 * 3.14159);

			float pitch = atan2(accelerationDirection.y, sqrt(accelerationDirection.x * accelerationDirection.x + accelerationDirection.z * accelerationDirection.z));
			pitch = fmod(pitch + 2 * 3.14159, 2 * 3.14159);

			o.setOrientation(glm::vec3(-rollAngle/2, 1.5-yaw+yawAngle/2, pitch+1.5+rollAngle/2));


			// Check left edge
			if (objPosition.x + -objSize.x < oMin.x) {
				o.setVelocity(glm::vec3(0.3 * velocity.x * -1, velocity.y, velocity.z));
				o.move(glm::vec3(0.05, 0, 0));
				//o.setOrientation(glm::vec3(0, 1.5, 0));
				//std::cout << "Reached left edge" << std::endl;

			}
			// Check right edge
			if (objPosition.x + objSize.x > oMax.x) {
				o.setVelocity(glm::vec3(0.3 * velocity.x * -1, velocity.y, velocity.z));
				//o.setPosition(glm::vec3(oMax.x - objSize.x, objPosition.y, objPosition.z));
				o.move(glm::vec3(-0.05, 0, 0));
				//o.setOrientation(glm::vec3(0, -1.5, 0));
				//std::cout << "Reached right edge" << std::endl;
				//std::cout << tickCount<< std::endl;
				
			}
			// Check top edge
			if (objPosition.y + objSize.y > oMax.y) {
				o.setVelocity(glm::vec3(velocity.x, 0.3 * velocity.y * -1, velocity.z));
				
				o.move(glm::vec3(0, -0.05, 0));
				//std::cout << "Reached top edge" << std::endl;
				
			}
			// Check bottom edge
			if (objPosition.y + -objSize.y < oMin.y/2 + 5.1 ) {
				//o.setVelocity(glm::vec3(velocity.x, 0.3 * velocity.y * -1, velocity.z));
				//o.setPosition(glm::vec3(objPosition.x , oMin.y / 2 + 7 + objSize.y  , objPosition.z));
				//o.move(glm::vec3(0.0, 0.05, 0.0));
				//std::cout << "Reached bottom edge" << std::endl;
				
			}
			// Check back edge
			if (objPosition.z + -objSize.z < oMin.z) {
				o.setVelocity(glm::vec3(velocity.x, velocity.y, 0.3 * velocity.z * -1));
				o.move(glm::vec3(0.0, 0.0, 0.05));
				std::cout << "Reached back edge" << std::endl;
			}
			// Check front edge
			if (objPosition.z + objSize.z > oMax.z) {
				o.setVelocity(glm::vec3(velocity.x, velocity.y, 0.3 * velocity.z * -1));
				o.move(glm::vec3(0.0, 0.0, -0.05));
				std::cout << "Reached front edge" << std::endl;
			}

			//o.tick(diffSeconds);
		}

		//BALSS
		for (auto& o : balls.objects) {
			auto inverseCam = glm::inverse(cameraRotation);
			auto gravityInCam = glm::vec3(inverseCam * glm::vec4(0.0, -9.8, 0.0, 0.0));


			glm::vec3 ballSize(2.1, 2.0, 2.1);

			o.applyForce(gravityInCam);
			//o.applyForce(gravityDirection);//glm::vec3(0.0, -9.8, 0.0));
			glm::vec3 velocity = o.getVelocity();
			glm::vec3 acceleration = o.getAcceleration();
			auto objPosition = o.getPosition();
			auto objScale = o.getScale();
			//temp size till i figure out how to get it
			auto objSize = ballSize;

			// Check left edge
			if (objPosition.x + -objSize.x < oMin.x) {
				o.setVelocity(glm::vec3(0.3 * velocity.x * -1, velocity.y, velocity.z));
				o.move(glm::vec3(0.15, 0, 0));
				//o.setOrientation(glm::vec3(0, 1.5, 0));
				//std::cout << "Reached left edge" << std::endl;

			}
			// Check right edge
			if (objPosition.x + objSize.x > oMax.x) {
				o.setVelocity(glm::vec3(0.3 * velocity.x * -1, velocity.y, velocity.z));
				o.move(glm::vec3(-0.15, 0, 0));
				//o.setOrientation(glm::vec3(0, -1.5, 0));
				//std::cout << "Reached right edge" << std::endl;
				
				
			}
			// Check top edge
			if (objPosition.y + objSize.y > oMin.y/2 + 5.0) {
				o.setVelocity(glm::vec3(velocity.x, 0.3 * velocity.y * -1, velocity.z));
				o.move(glm::vec3(0, -0.20, 0));
				//std::cout << "Reached top edge" << std::endl;
				
			}
			// Check bottom edge
			if (objPosition.y + -objSize.y < oMin.y / 2) {
				o.setVelocity(glm::vec3(velocity.x, 0.3 * velocity.y * -1, velocity.z));
				o.move(glm::vec3(0.0, 0.05, 0.0));
				//std::cout << "Reached bottom edge" << std::endl;
				
			}
			// Check back edge
			if (objPosition.z + -objSize.z < oMin.z) {
				o.setVelocity(glm::vec3(velocity.x, velocity.y, 0.3 * velocity.z * -1));
				o.move(glm::vec3(0.0, 0.0, 0.15));
				//std::cout << "Reached back edge" << std::endl;
			}
			// Check front edge
			if (objPosition.z + objSize.z > oMax.z) {
				o.setVelocity(glm::vec3(velocity.x, velocity.y, 0.3 * velocity.z * -1));
				o.move(glm::vec3(0.0, 0.0, -0.15));
				//std::cout << "Reached front edge" << std::endl;
			}

			// Check for collisions with other balls
			for (auto& other : balls.objects) {

				// Skip self collision
				if (&o == &other) continue;

				auto otherPosition = other.getPosition();
				auto otherScale = other.getScale();
				//temp radius till i figure out how to find radius
				auto otherSize = ballSize;

				// Calculate distance betweenthe two balls
				float distance = glm::distance(objPosition, otherPosition);
				float sumRadius = objSize.x + otherSize.x;

				if (distance < sumRadius) {
					
					//reverse velocitioes
					
					glm::vec3 newVel1, newVel2, newPos1, newPos2;
					newVel1 = glm::vec3(-o.getVelocity().x , -o.getVelocity().y , -o.getVelocity().z);
					
					newVel2 = glm::vec3(-other.getVelocity().x , -other.getVelocity().y , -other.getVelocity().z );


					//o.setVelocity(newVel1);
					//o.move(glm::vec3(newPos1.x ,newPos1.y, newPos1.z));
					//other.setVelocity(newVel2);
					//other.move(glm::vec3(newPos2.x , newPos2.y, newPos2.z ));

					//move along collision normal
					glm::vec3 moving = glm::normalize(otherPosition+ballSize - objPosition+ ballSize);
					o.move(-moving*glm::vec3(0.05,0.05,0.05));
					other.move(moving * glm::vec3(0.05, 0.05, 0.05));


				}
			}
			o.tick(diffSeconds);	
		}

		//collision between boat and balls
		for (auto& ship : scene.objects) {
			for (auto& ball : balls.objects) {
				auto shipPos = ship.getPosition();
				auto shipSize = glm::vec3(5, 4.4, 2.1);
				auto ballPos = ball.getPosition();
				auto ballSize = glm::vec3(1.1, 3.0, 1.1);

				if (ballPos.y + ballSize.y >= shipPos.y - shipSize.y) {
					
					//ball.move(glm::vec3(0, -0.07, 0));
					ship.move(glm::vec3(0,0.05,0));
					ship.setVelocity(glm::vec3(ship.getVelocity().x, 0.3 * ship.getVelocity().y * -1, ship.getVelocity().z));
					
				}

				//ball.tick(diffSeconds);
			}
			ship.tick(diffSeconds);
		}


		//bird animation
		for (auto& animator : birds.animators) {
			animator.tick(diffSeconds);
		}

		

		// Clear the OpenGL "context".
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render each object in the scene.
		
		for (auto& o : ocean.objects) {
			o.render(window, mainShader);
		}
		for (auto& o : balls.objects) {
			o.render(window, mainShader);
		}
		for (auto& o : scene.objects) {
			o.render(window, boatShader);
		}
		
		for (auto& o : birds.objects) {
			o.render(window, boatShader);
		}

		window.display();
	}

	return 0;
}




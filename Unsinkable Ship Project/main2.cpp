/*
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
		//phongLighting(),
		textureMapping(),
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
	shipwithsails.grow(glm::vec3(0.1, 0.1, 0.1));
	shipwithsails.move(glm::vec3(0, 0,0));
	shipwithsails.rotate(glm::vec3(0,1.5,0));
	//bottle.addChild(std::move(shipwithsails));
	
	shipwithsails.setVelocity(glm::vec3(0.0, 5.0, 0.0));
	//shipwithsails.setAcceleration(glm::vec3(0.0f, -9.8, 0.0));
	//shipwithsails.setRotationalAcceleration(glm::vec3(0.0, 0.1, 0.0));
	shipwithsails.setMass(1.0);
	//shipwithsails.applyForce(glm::vec3(0.0, -9.8, 0.0));

	
	auto balls = assimpLoad("models/sphere/3d-model.obj", true);
	//balls.grow(glm::vec3(50, 50, 50));
	balls.grow(glm::vec3(0.05, 0.05, 0.05));
	balls.setVelocity(glm::vec3(2.0, 10.0, 0.0));
	balls.setMass(1.0);
	
	

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
		textureMapping(),
		//phongLighting(),
		std::move(objects),
		std::move(animators)

	};

}
// Function to generate a random float between min and max
static float randomFloat(float min, float max) {
	return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
}
static Scene OceanBalls() {
	

	std::vector<Object3D> objects;
	auto ballModel = assimpLoad("models/sphere/3d-model.obj", true);
	ballModel.grow(glm::vec3(0.05, 0.05, 0.05));

	//ballModel.setVelocity(glm::vec3(0.0, 0.0, 0.0));
	ballModel.setMass(1);


	for (int i = 0; i < 300; ++i) {
		auto ball = ballModel;

		// random positions
		float ranX = randomFloat(-40.0, 40.0);
		float ranY = randomFloat(-30.0, -10.0);
		float ranZ = randomFloat(-2.0, -2.0);

		ball.setPosition(glm::vec3(ranX, ranY, ranZ));

		// random velocities
		float ranXvel = randomFloat(-3.0, 3.0);
		float ranYvel = randomFloat(-2.0, 2.0);
		float ranZvel = randomFloat(-1.0, 1.0);

		// Set the velocity of the ball
		ball.setVelocity(glm::vec3(ranXvel, ranYvel, ranZvel));

		// Add the ball to the list of objects
		objects.push_back(std::move(ball));
	}
	return Scene{
		//textureMapping(),
		phongLighting(),
		std::move(objects)
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
	auto ocean = OceanBalls();
	//auto scene = bunny();
	//auto scene = lifeOfPi();

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

	// Ready, set, go!
	for (auto& animator : scene.animators) {
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
		//
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			yawAngle += 0.005;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			yawAngle -= 0.005;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			rollAngle += 0.005;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			rollAngle -= 0.005;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			rollAngle = 0.0;
			yawAngle = 0.0;
			for (auto& o : scene.objects) {
				o.setPosition(glm::vec3(0,0,0));
			}
			for (auto& ball : ocean.objects) {
				float ranX = randomFloat(-40.0, 40.0);
				float ranY = randomFloat(-30.0, -10.0);
				float ranZ = randomFloat(-2.0, -2.0);

				ball.setPosition(glm::vec3(ranX, ranY, ranZ));
			}
		}
		//update camera based on key input
		auto yawRotation = glm::rotate(glm::mat4(1.0), yawAngle, glm::vec3(0, 0, 1));
		auto rollRotation = glm::rotate(glm::mat4(1.0), rollAngle, glm::vec3(1, 0, 0));
		auto cameraRotation = yawRotation * rollRotation;
		auto cameraView = glm::lookAt(cameraPosition, glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
		auto camera = cameraView * cameraRotation;
		mainShader.setUniform("view", camera);

		
		// Calculate bounds relative to the camera's rotation
		
		
		//auto gravityDirection = -glm::normalize(glm::vec3(1, 1, 0)) * 9.8f;
		auto now = c.getElapsedTime();
		auto diff = now - last;
		auto diffSeconds = diff.asSeconds();
		last = now;
		
		//animation
		for (auto& animator : scene.animators) {
			animator.tick(diffSeconds);

		}
		//glm::vec3 cameraForward = glm::normalize(glm::vec3(cameraRotation * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));

		//simulation
		for (auto& o : scene.objects) {
			//put gravity in camera space
			auto inverseCam = glm::inverse(cameraRotation);
			auto gravityInCam = glm::vec3(inverseCam * glm::vec4(0.0, -9.8, 0.0, 0.0));
			
			//o.setOrientation(cameraForward);

			auto LeftBound = glm::vec3(inverseCam * glm::vec4(-75 / 2, 0, 0, 1));//windowSize.x
			auto RightBound = glm::vec3(inverseCam * glm::vec4(75 / 2, 0, 0, 1));
			auto TopBound = glm::vec3(inverseCam * glm::vec4(0, 75 / 2, 0, 1));//windowSize.y
			auto BottomBound = glm::vec3(inverseCam * glm::vec4(0, -5 / 2, 0, 1));
			auto FrontBound = glm::vec3(inverseCam * glm::vec4(0, 0, 0 / 2, 1));
			auto BackBound = glm::vec3(inverseCam * glm::vec4(0, 0, -2 / 2, 1));

			o.applyForce(gravityInCam);
			//o.applyForce(glm::vec3(0.0, -9.8, 0.0));
			glm::vec3 velocity = o.getVelocity();
			glm::vec3 acceleration = o.getAcceleration();
			auto objPosition = o.getPosition();
			auto objScale = o.getScale();
			auto objSize = glm::vec3(objScale.x, objScale.y, objScale.z); //x and y valuses| there has to be a way to get the bounds of the object
			//std::cout << "Object position: " << objPosition.x << ", " << objPosition.y << std::endl;
			//std::cout << "Object velocity: " << velocity.x << ", " << velocity.y << std::endl;
			//std::cout << "Object acceleration: " << acceleration.x << ", " << acceleration.y << std::endl;

			//windowSize.x *= objScale.x;
			//windowSize.y *= objScale.y;
			// Check left edge
			if (objPosition.x +objSize.x <= LeftBound.x){//-1.0 * windowSize.x) {
				o.setVelocity(glm::vec3(0.3* velocity.x * -1,velocity.y, velocity.z));
				o.move(glm::vec3(0.2,0,0));
				o.setOrientation(glm::vec3(0, 1.5, 0));
				//o.rotate(glm::vec3(0, 1.5, 0));

				//velocity.x *= -1;
				//o.applyForce(glm::vec3(30, 0.0, 0.0));
				std::cout << "Reached left edge" << std::endl;
			}
			// Check right edge
			if (objPosition.x + objSize.x >= RightBound.x){// windowSize.x) {
				o.setVelocity(glm::vec3(0.3*velocity.x * -1, velocity.y, velocity.z));
				o.move(glm::vec3(-0.2, 0, 0));
				o.setOrientation(glm::vec3(0, -1.5, 0));
				//velocity.x *= -1;
				//o.applyForce(glm::vec3(-30, 0.0, 0.0));
				std::cout << "Reached right edge" << std::endl;
			}
			// Check top edge
			if (objPosition.y + objSize.y >= TopBound.y){// windowSize.y) {
				o.setVelocity(glm::vec3(velocity.x, 0.3*velocity.y * -1, velocity.z));
				o.move(glm::vec3(0, -0.1, 0));
				
				//velocity.y *= -1;
				//o.applyForce(glm::vec3(0.0, -1, 0.0));
				std::cout << "Reached top edge" << std::endl;
			}
			// Check bottom edge
			if (objPosition.y + objSize.y <= BottomBound.y){//-1.0 *windowSize.y) {
				o.setVelocity(glm::vec3(velocity.x, 0.3*velocity.y * -1, velocity.z));
				o.move(glm::vec3(0.0, 0.05, 0.0));
				//velocity.y *= -1;
				//o.applyForce(glm::vec3(0.0, 10, 0.0));
				//std::cout << "Reached bottom edge" << std::endl;
			}
			// Front edge
			if (objPosition.z + objSize.z <= TopBound.z) {
				o.setVelocity(glm::vec3(velocity.x, velocity.y , 0.3 * velocity.z * -1));
				o.move(glm::vec3(0.0, 0.0, 0.05));
				//velocity.y *= -1;
				//o.applyForce(glm::vec3(0.0, 10, 0.0));
				std::cout << "Reached front edge" << std::endl;
			}
			// Back edge
			if (objPosition.z + objSize.z <= BottomBound.z) {//-1.0 *windowSize.y) {
				o.setVelocity(glm::vec3(velocity.x, velocity.y, 0.3 * velocity.z * -1));
				o.move(glm::vec3(0.0, 0.0, 0.05));
				//velocity.y *= -1;
				//o.applyForce(glm::vec3(0.0, 10, 0.0));
				std::cout << "Reached back edge" << std::endl;
			}

			// Update position with velocity
			//o.move(velocity * diffSeconds);
			o.tick(diffSeconds);
		}

		//BALSS
		for (auto& o : ocean.objects) {
			auto inverseCam = glm::inverse(cameraRotation);
			auto gravityInCam = glm::vec3(inverseCam * glm::vec4(0.0, -9.8, 0.0, 0.0));

			auto LeftBound = glm::vec3(inverseCam * glm::vec4(-75 / 2, 0, 0, 1));//windowSize.x
			auto RightBound = glm::vec3(inverseCam * glm::vec4(75 / 2, 0, 0, 1));
			auto TopBound = glm::vec3(inverseCam * glm::vec4(0, 55 / 2, 0, 1));//windowSize.y
			auto BottomBound = glm::vec3(inverseCam * glm::vec4(0, -55 / 2, 0, 1));
			auto FrontBound = glm::vec3(inverseCam * glm::vec4(0, 0,30 / 2, 1));
			auto BackBound = glm::vec3(inverseCam * glm::vec4(0, 0, -30 / 2, 1));

			glm::vec3 ballSize(0.9, 0.9, 0.9);

			o.applyForce(gravityInCam);
			//o.applyForce(gravityDirection);//glm::vec3(0.0, -9.8, 0.0));
			glm::vec3 velocity = o.getVelocity();
			glm::vec3 acceleration = o.getAcceleration();
			auto objPosition = o.getPosition();
			auto objScale = o.getScale();
			//temp size till i figure out how to get it
			auto objSize = ballSize;
			
			// Check left edge
			if (objPosition.x + objSize.x <= LeftBound.x) {//-1.0 * windowSize.x) {
				o.setVelocity(glm::vec3(0.1 * velocity.x * -1, velocity.y, velocity.z));
				//o.setPosition(glm::vec3(-39 + objSize.x, objPosition.y, 0));
				o.move(glm::vec3(0.05, 0.0, 0.0));
				//velocity.x *= -1;
				//o.applyForce(glm::vec3(30, 0.0, 0.0));
				//std::cout << "Reached left edge" << std::endl;
			}
			// Check right edge
			if (objPosition.x + objSize.x >= RightBound.x) {// windowSize.x) {
				o.setVelocity(glm::vec3(0.1 * velocity.x * -1, velocity.y, velocity.z));
				//o.setPosition(glm::vec3(39 + objSize.x, objPosition.y, 0));
				o.move(glm::vec3(-0.05, 0.0, 0.0));
				//velocity.x *= -1;
				//o.applyForce(glm::vec3(-30, 0.0, 0.0));
				//std::cout << "Reached right edge" << std::endl;
			}
			// Check top edge
			if (objPosition.y + objSize.y >= TopBound.y) {// windowSize.y) {
				o.setVelocity(glm::vec3(velocity.x, 0.1 * velocity.y * -1, velocity.z));
				//o.setPosition(glm::vec3(objSize.x, -10 - objPosition.y, 0));
				o.move(glm::vec3(0.0, -0.05, 0.0));
				//velocity.y *= -1;
				//o.applyForce(glm::vec3(0.0, -1, 0.0));
				//std::cout << "Reached top edge" << std::endl;
			}
			// Check bottom edge
			if (objPosition.y + objSize.y <= BottomBound.y) {//-1.0 *windowSize.y) {
				o.setVelocity(glm::vec3(velocity.x, 0.1 * velocity.y * -1, velocity.z));
				//o.setPosition(glm::vec3( objSize.x, 2 + objPosition.y, 0));
				o.move(glm::vec3(0.0, 0.05, 0.0));
				//velocity.y *= -1;
				//o.applyForce(glm::vec3(0.0, 9.8, 0.0));
				//std::cout << "Reached bottom edge" << std::endl;
			}
			// Front edge
			if (objPosition.z + objSize.z <= TopBound.z) {
				o.setVelocity(glm::vec3(velocity.x, velocity.y, 0.1 * velocity.z * -1));
				o.move(glm::vec3(0.0, 0.0, 0.05));
				//velocity.y *= -1;
				//o.applyForce(glm::vec3(0.0, 10, 0.0));
				//std::cout << "Reached bottom edge" << std::endl;
			}
			// Back edge
			if (objPosition.z + objSize.z <= BottomBound.z) {//-1.0 *windowSize.y) {
				o.setVelocity(glm::vec3(velocity.x, velocity.y, 0.1 * velocity.z * -1));
				o.move(glm::vec3(0.0, 0.0, 0.05));
				//velocity.y *= -1;
				//o.applyForce(glm::vec3(0.0, 10, 0.0));
				//std::cout << "Reached bottom edge" << std::endl;
			}
			

			
			// Check for collisions with other balls
			for (auto& other : ocean.objects) {
				
				// Skip self collision
				if (&o == &other) continue;

				auto otherPosition = other.getPosition();
				auto otherScale = other.getScale();
				//temp radius till i figure out how to find radius
				auto otherSize = ballSize;

				// Calculate distance betweenthe two balls
				float distance = glm::distance(objPosition, otherPosition);
				float sumOfRadius = objSize.x + otherSize.x;
				
				if (distance < sumOfRadius) {
					
					//reverse velocitioes
					glm::vec3 newVel1, newVel2, newPos1, newPos2;
					newVel1 = -o.getVelocity();
					newPos1 = o.getPosition();
					newVel2 = other.getVelocity();
					newPos2 = other.getPosition();

					
					o.setVelocity(newVel1);
					o.move(glm::vec3(newVel1.x*0.001 , newVel1.y * 0.001 , 0));
					other.setVelocity(newVel2);
					other.move(glm::vec3(newVel2.x * 0.001 , newVel2.y * 0.001 , 0));
					

				}
			}
			o.tick(diffSeconds);
		}


		// Clear the OpenGL "context".
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render each object in the scene.
		for (auto& o : ocean.objects) {

			o.render(window, mainShader);
		}
		
		for (auto& o : scene.objects) {
			
			o.render(window, mainShader);
		}

		window.display();
	}

	return 0;
}
*/




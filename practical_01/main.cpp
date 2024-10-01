#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::A, 	//Player1 UP
	Keyboard::Z, 	//Player1 DOWN
	Keyboard::Up, 	//Player2 UP
	Keyboard::Down,	//Player2 DOWN
};

const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;
const float initialVelocityX = 100.f;
const float initialVelocityY = 60.f;
const float velocityMultiplier = 1.1f;

Vector2f ballVelocity;
bool isPlayer1Serving = false;

CircleShape ball;
RectangleShape paddles[2];

void Load(){
	//set size and origin of paddles
	for(auto &p : paddles){
		p.setSize(paddleSize);
		p.setOrigin(paddleSize / 2.f);
	}
	
	//set size and origin of ball
	ball.setRadius(ballRadius);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	
	//reset paddle position
	paddles[0].setPosition(Vector2f(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f));
	paddles[1].setPosition(Vector2f(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f));
	
	//reset ball position
	ball.setPosition(gameWidth / 2, gameHeight / 2);
	
	ballVelocity = { (isPlayer1Serving ? initialVelocityX : -initialVelocityX), initialVelocityY };
}

void Reset(){
	//reset paddle position
	paddles[0].setPosition(Vector2f(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f));
	paddles[1].setPosition(Vector2f(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f));
	
	//reset ball position
	ball.setPosition(gameWidth / 2, gameHeight / 2);
}

void Update(RenderWindow &window){
	//reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	
	//check and consume events
	Event event;
	while(window.pollEvent(event)){
		if(event.type == Event::Closed){
			window.close();
			return;
		}
	}
	
	//quit via ESC key
	if(Keyboard::isKeyPressed(Keyboard::Escape)){
		window.close();
	}
	
	//handle paddle movement
	float direction = 0.0f;
	
	if(Keyboard::isKeyPressed(controls[0])){
		direction--;
	}
	if(Keyboard::isKeyPressed(controls[1])){
		direction++;
	}
	paddles[0].move(Vector2f(0.f, direction * paddleSpeed * dt));

	direction = 0.f;

	if (Keyboard::isKeyPressed(controls[2])) {
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		direction++;
	}
	paddles[1].move(Vector2f(0.f, direction * paddleSpeed * dt));
	
	//move the ball
	ball.move(ballVelocity * dt);
	
	//check ball collision
	const floast bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	
	if(by > gameHeight){
		//bottom wall
		ballVelocity.x *= velocityMultiplier;
		ballVelocity.y *= -velocityMultiplier;
		ball.move(Vector2(0.f, -10.f));
	} else if(by < 0){
		//top wall
		ballVelocity.x *= velocityMultiplier;
		ballVelocity.y *= -velocityMultiplier;
		ball.move(Vector2(0.f, 10.f));
	} else if(bx > gameWidth || bx < 0){ //if someone scores, reset
		Reset();
/*
	} else if(bx < paddleSize.x + paddleOffsetWall && by > paddles[0].getPosition().y - (paddleSize.y * 0.5) && by < paddles[0].getPosition.y + (paddleSize.y * 0.5)){ //if the ball collides with the left paddle, bounce the ball
		
	} else if(bx < paddleSize.x + paddleOffsetWall && by > paddles[1].getPosition().y - (paddleSize.y * 0.5) && by < paddles[1].getPosition.y + (paddleSize.y * 0.5)){ //if the ball collides with the right paddle, bounce the ball
*/
	};
}

void Render(RenderWindow &window){
	//draw everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}

int main(){
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while(window.isOpen()){
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}
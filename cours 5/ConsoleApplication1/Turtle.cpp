#include "Turtle.hpp"
#include "SFML/Graphics/Rect.hpp"
#include <vector>

Turtle::Turtle() {

	auto& bdy = comps[0];
	bdy = sf::CircleShape(50);
	bdy.setFillColor(sf::Color::Green);
	bdy.setOutlineColor(sf::Color::White);
	bdy.setOutlineThickness(2);
	bdy.setOrigin(48, 48);

	auto& head = comps[1];
	head = sf::CircleShape(20);
	head.setFillColor(sf::Color::Cyan);
	head.setOutlineColor(sf::Color::Black);
	head.setOutlineThickness(1);
	head.setOrigin(bdy.getPosition() + sf::Vector2f(15, 70));

	auto& trail = comps[2];
	trail = sf::CircleShape(10);
	trail.setFillColor(sf::Color::Yellow);
	trail.setOutlineColor(sf::Color::White);
	trail.setOutlineThickness(1);
	trail.setOrigin(bdy.getPosition() + sf::Vector2f(8, -35));

	tex.create(2048, 2048);
	tex.clear(sf::Color(0,0,0,0));
	
	bool penEnabled = false;
}


void Turtle::update(double dt) {
	
	while (cmds)
		cmds = applyCmdInterp(cmds, dt);

}

void Turtle::draw(sf::RenderWindow& win) {
	tex.display();
	sf::Sprite sprite(tex.getTexture());
	win.draw(sprite);

	for (auto& c : comps)
		win.draw(c, trs);
	win.draw(dir, trs);
	
}


void Turtle::appendCmd(Cmd* cmd) {
	if (cmds)
		cmds = cmds->append(cmd);
	else
		cmds = cmd;
}

Cmd* Turtle::applyCmd(Cmd* cmd) {
	switch (cmd->type) {
	case Advance:
		trs.translate(0, -cmd->value);
		if (penEnabled) {
			sf::CircleShape pen(8);
			pen.setFillColor(penColor);
			pen.setOrigin(8, 8);
			pen.setPosition(trs.transformPoint(sf::Vector2f(0, 0)));
			tex.draw(pen);
		}
		break;
	case Rotate:	trs.rotate(cmd->value); break; break;
	case PenUp:		penEnabled = false; break;
	case PenDown:	penEnabled = true; break;
	case PenColor:
		penColor = cmd->col;
		break;
	default:
		break;
	}

	return nullptr;
}

Cmd* Turtle::applyCmdInterp(Cmd* cmd, double dt) {
	dt = 1.0f / 60.0f;
	float ratio = cmd->timer / cmd->maxDuration;
	float speed = 1.0f / cmd->maxDuration;
	bool destroy = false;
	switch (cmd->type) {
	case Advance:
		trs.translate(0, -cmd->value * dt * speed);
		if (penEnabled) {
			sf::CircleShape pen(8);
			pen.setFillColor(penColor);
			pen.setOrigin(8, 8);
			pen.setPosition(trs.transformPoint(sf::Vector2f(0, 0)));
			tex.draw(pen);
		}
		break;
	case Rotate:
		trs.rotate(cmd->value * dt * speed);
		break;
	case PenUp:		penEnabled = false;
		destroy = true;
		break;
	case PenDown:	penEnabled = true;
		destroy = true;
		break;
	case PenColor:
		penColor = cmd->col;
		destroy = true;
		break;
	default:
		break;
	}

	cmd->timer += dt;
	if (cmd->timer >= cmd->maxDuration)
		destroy = true;

	if (!destroy) {
		return cmd;
	}
	else {
		cmd = cmd->popFirst();
		return cmd;
	}
}

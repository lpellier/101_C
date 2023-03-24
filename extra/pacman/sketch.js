// ? Pac man
// ? https://gameinternals.com/understanding-pac-man-ghost-behavior

// ? dots (for scoring)
// ? ghost ennemies

// ? pathways
	// ? if pacman goes to edge of screen, he teleports to the opposite
	// ? there needs to be dots on pathways

// ? power ups
	// ? when pacman eats one, he becomes invincible and can kill the ghosts
	// ? ghosts respawn after a certain amount of time

// ? collisions
	// ? if pacman touches a ghost, game over

// ? multiple lives

// ? pacman is constantly moving
	// ? arrow keys to change direction

// ? victory screen / game over screen

// to-do list:
	// ? create the following classes:
		// ? pacman
		// ? ghosts
		// ? dots
		// ? game -> map, ennemies, player, scoring
	
	// ? initialize variables (player, ghosts, score, map etc)

	// ? draw background
	// ? 

let grid = [
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ],
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, ], 
	[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, ], 
	[1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, ], 
	[1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, ], 
	[1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, ], 
	[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, ], 
	[1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, ], 
	[1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, ], 
	[1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, ], 
	[1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, ], 
	[0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, ], 
	[0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, ], 
	[0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, ], 
	[1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, ], 
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ], 
	[1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, ], 
	[0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, ], 
	[0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, ], 
	[0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, ], 
	[1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, ], 
	[1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, ], 
	[1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, ], 
	[1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, ], 
	[1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, ], 
	[1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, ], 
	[1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, ], 
	[1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, ], 
	[1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, ], 
	[1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, ], 
	[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, ], 
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, ], 
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ], 
	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ], 
	];

const TILE_WIDTH = 16;
const TILE_HEIGHT = 16;

const GRID_WIDTH = 28;
const GRID_HEIGHT = 36;
const PACMAN_DIAMETER = TILE_WIDTH;

let canvas;

function dijkstra(grid, startNode, endNode) {
	const unvisitedNodes = getNodes(grid);
	const distances = {};
	const previousNodes = {};
  
	// Initialize distances to infinity and previous nodes to null
	for (let node of unvisitedNodes) {
	  distances[node.id] = Infinity;
	  previousNodes[node.id] = null;
	}
	distances[startNode.id] = 0;
  
	while (unvisitedNodes.length > 0) {
	  // Find node with smallest distance
	  let currentNode = null;
	  for (let node of unvisitedNodes) {
		if (currentNode == null || distances[node.id] < distances[currentNode.id]) {
		  currentNode = node;
		}
	  }
  
	  // Stop if end node is reached
	  if (currentNode === endNode) {
		break;
	  }
  
	  // Mark current node as visited
	  unvisitedNodes.splice(unvisitedNodes.indexOf(currentNode), 1);
  
	  // Update distances of neighbors
	  for (let neighbor of getNeighbors(currentNode, grid)) {
		let tentativeDistance = distances[currentNode.id] + 1; // assuming each move has a cost of 1
  
		if (tentativeDistance < distances[neighbor.id]) {
		  distances[neighbor.id] = tentativeDistance;
		  previousNodes[neighbor.id] = currentNode;
		}
	  }
	}
  
	// Construct shortest path
	const shortestPath = [];
	let currentNode = endNode;
  
	while (previousNodes[currentNode.id] != null) {
	  shortestPath.unshift(currentNode);
	  currentNode = previousNodes[currentNode.id];
	}
  
	// Add start node to path
	shortestPath.unshift(startNode);
  
	return shortestPath;
  }
  
  // Returns an array of all nodes in the grid
  function getNodes(grid) {
	const nodes = [];
  
	for (let row of grid) {
	  for (let node of row) {
		nodes.push(node);
	  }
	}
  
	return nodes;
  }
  
  // Returns an array of neighboring nodes
  function getNeighbors(node, grid) {
	const neighbors = [];
	const { row, col } = node;
  
	if (row > 0) neighbors.push(grid[row - 1][col]); // top neighbor
	if (row < grid.length - 1) neighbors.push(grid[row + 1][col]); // bottom neighbor
	if (col > 0) neighbors.push(grid[row][col - 1]); // left neighbor
	if (col < grid[0].length - 1) neighbors.push(grid[row][col + 1]); // right neighbor
  
	return neighbors.filter(neighbor => !neighbor.isWall);
  }

class Ghost {
	constructor(posX, posY, color) {
		this.pos = {x: posX, y: posY};
		this.dir = {x: 0, y: 0};
		this.next_move = {x: 0, y: 0};
		this.color = color;
		this.side = PACMAN_DIAMETER;
		this.path = [];
	}

	draw() {
		push();
		// noStroke();
		fill(this.color);
		rect(this.pos.x * TILE_WIDTH, this.pos.y * TILE_HEIGHT, this.side);
		for (let cell of this.path) {
			fill('red');
			circle((cell.col + 0.5) * TILE_WIDTH, (cell.row + 0.5) * TILE_HEIGHT, 5);
		} 
		pop();
	}

	calculate() {
		let test = [];
		let start_node, end_node;
		let id = 0;
		for (let r = 0; r < grid.length; r++) {
			let row = [];
			for (let c = 0; c < grid[r].length; c++) {
				let obj = {
					row: r,
					col: c,
					isWall: (grid[r][c] === 1 ? true : false),
					id: id
				}
				if (r === Math.floor(this.pos.y) && c === Math.floor(this.pos.x))
					start_node = obj;
				if (r === Math.floor(pacman.pos.y) && c === Math.floor(pacman.pos.x))
					end_node = obj;
				row.push(obj)
				id++;
			}
			test.push(row);
		}

		this.path = dijkstra(test, start_node, end_node)
	}

	move() {
		if (this.path.length === 0) return;
		while (this.path[0].col === Math.floor(this.pos.x) && this.path[0].row === Math.floor(this.pos.y))  {
			this.path.splice(0, 1);
			if (this.path.length === 0) return;
		}
		if (this.path[0].col > this.pos.x) this.next_move = {x: 1, y: 0};
		else if (this.path[0].col < this.pos.x) this.next_move = {x: -1, y: 0};
		else if (this.path[0].row > this.pos.y) this.next_move = {x: 0, y: 1};
		else if (this.path[0].row < this.pos.y) this.next_move = {x: 0, y: -1};
		// console.log(this.next_move)

		this.pos.x = Number(this.pos.x.toFixed(1));
		this.pos.y = Number(this.pos.y.toFixed(1));
	
		if (this.pos.x === Math.floor(this.pos.x) && this.pos.y === Math.floor(this.pos.y) && grid[Math.floor(this.pos.y + this.next_move.y)][Math.floor(this.pos.x + this.next_move.x)] !== 1)
			this.dir = this.next_move;

		let adder = { x: 0, y: 0 };
		if (this.dir.x > 0)	adder.x = 1;
		else				adder.x = 0;
		if (this.dir.y > 0)	adder.y = 1;
		else				adder.y = 0;
		
		let check = {
			x: Number((this.pos.x + adder.x).toFixed(1)),
			y: Number((this.pos.y + adder.y).toFixed(1))
		}

		if (this.dir.x < 0 || this.dir.y < 0) {
			check.x += Number((this.dir.x * 0.1).toFixed(1));
			check.y += Number((this.dir.y * 0.1).toFixed(1));	
		}
		
		// console.log(check)

		if (grid[Math.floor(check.y)][Math.floor(check.x)] !== 1) {
			this.pos.x += this.dir.x * 0.1;
			this.pos.y += this.dir.y * 0.1;
		}

		if (this.pos.x > 28.5)		this.pos.x = -0.1;
		else if (this.pos.x < 0)	this.pos.x = 28.6; 
	}
}

class PacMan {
	constructor(posX, posY) {
		this.pos = {x: posX + 0.5, y: posY + 0.5};
		this.dir = {x: 0, y: 0};
		this.next_move = {x: 0, y: 0};
		this.radius = PACMAN_DIAMETER / 2;
	}

	draw() {
		push()
		noStroke()
		fill("yellow")
		circle(this.pos.x * TILE_WIDTH, this.pos.y * TILE_HEIGHT, PACMAN_DIAMETER)
		fill("black")
		circle(
			this.pos.x * TILE_WIDTH + this.dir.x * PACMAN_DIAMETER / 5, 
			this.pos.y * TILE_HEIGHT + this.dir.y * PACMAN_DIAMETER / 5, 
			PACMAN_DIAMETER / 3
			)
			pop()
		}

	move() {
		this.pos.x = Number(this.pos.x.toFixed(1));
		this.pos.y = Number(this.pos.y.toFixed(1));
		// console.log(this.pos)
		let decimals = {x: Number((this.pos.x % 1).toFixed(1)), y: Number((this.pos.y % 1).toFixed(1))};
	
		if (decimals.x === 0.5 && decimals.y === 0.5 && grid[Math.floor(this.pos.y + this.next_move.y)][Math.floor(this.pos.x + this.next_move.x)] !== 1)
			this.dir = this.next_move;

		let adder = { x: 0, y: 0 };
		if (this.dir.x > 0)	adder.x = 0.5;
		else				adder.x = -0.5;
		if (this.dir.y > 0)	adder.y = 0.5;
		else				adder.y = -0.5;
		
		let check = {
			x: Number((this.pos.x + adder.x).toFixed(1)),
			y: Number((this.pos.y + adder.y).toFixed(1))
		}

		if (this.dir.x < 0 || this.dir.y < 0) {
			check.x += Number((this.dir.x * 0.1).toFixed(1));
			check.y += Number((this.dir.y * 0.1).toFixed(1));	
		}
		
		// console.log(check)

		if (grid[Math.floor(check.y)][Math.floor(check.x)] !== 1) {
			this.pos.x += this.dir.x * 0.1;
			this.pos.y += this.dir.y * 0.1;
		}

		if (this.pos.x > 28.5)		this.pos.x = -0.1;
		else if (this.pos.x < 0)	this.pos.x = 28.6; 
	}
}

function printGrid() {
	console.log("let grid = [");
	for (let y = 0; y < GRID_HEIGHT; y++) {
		let printStr = "[";	
		for (let x = 0; x < GRID_WIDTH; x++) {
			printStr += grid[y][x].toString() + ", ";
		}
		printStr += "],";
		console.log(printStr)
	}
	console.log("];");
}

let pacman;
let ghost;

function setup() {
	let canvas = createCanvas(GRID_WIDTH * TILE_WIDTH, GRID_HEIGHT * TILE_HEIGHT)
	background("black");
	let button = createButton('map done');
	button.position(0, 0);
	button.mousePressed(printGrid);

	pacman = new PacMan(14, 15);

	ghost = new Ghost(8, 8, "blue");
}

function drawMap() {
	for (let y = 0; y < GRID_HEIGHT; y++) {
		for (let x = 0; x < GRID_WIDTH; x++) {
			push()
			noStroke();
			if (grid[y][x] === 0) {
				fill("black")
			}
			else if (grid[y][x] === 1) {
				fill("green");
			}
			rect(x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
			pop()
		}
	}
}

function draw() {
	drawMap()
	pacman.draw();
	pacman.move();
	ghost.draw();
	if (frameCount % 60 === 0)
		ghost.calculate();
	ghost.move();
}

function keyPressed() {
	if (keyCode === (LEFT_ARROW))
		pacman.next_move = { x:-1, y:0 }	
	if (keyCode === (RIGHT_ARROW))
		pacman.next_move = { x:1, y:0 }
	if (keyCode === (UP_ARROW))
		pacman.next_move = { x:0, y:-1 }
	if (keyCode === (DOWN_ARROW))
		pacman.next_move = { x:0, y:1 }
}

function mousePressed() {
	let clicked = grid[Math.floor(mouseY / TILE_HEIGHT)][Math.floor(mouseX / TILE_WIDTH)]
	if (clicked === 0)
		grid[Math.floor(mouseY / TILE_HEIGHT)][Math.floor(mouseX / TILE_WIDTH)] = 1;
	else if (clicked === 1)
		grid[Math.floor(mouseY / TILE_HEIGHT)][Math.floor(mouseX / TILE_WIDTH)] = 0;
}

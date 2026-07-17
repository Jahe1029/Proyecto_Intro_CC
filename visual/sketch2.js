class Planet {
  constructor(data, radio, color) {
    this.file_name = data;
    this.r = radio;
    this.col = color;         // Pass a p5 color object, e.g., color(255, 0, 0)
    
    this.raw_text = [];     // Stays empty until preloaded
    this.positions = [];    // Populated during setup
    this.Index = 0;  // Tracks where the planet is in its orbit
  }

  // Call this inside p5's preload()
  loadFile() {
    this.raw_text = loadStrings(this.file_name);
	  console.log(this.raw_text);
  }

  // Call this inside p5's setup() to parse the '\t' data
  parseData() {
    for (let i = 0; i < this.raw_text.length; i++) {
      if (this.raw_text[i].trim() === "") continue;
      
      let tokens = this.raw_text[i].split('\t');
      let pos = createVector(float(tokens[0]), float(tokens[1]), float(tokens[2]));
      this.positions.push(pos);
    }
  }

  // Call this inside p5's draw() to update and render the sphere
  display() {
    // Safety check to ensure we have data left to read
    if (this.Index < this.positions.length) {
      let pos = this.positions[this.Index];

      push();
        translate(pos.x, pos.y, pos.z);
        noStroke();
        ambientMaterial(this.col);
        sphere(this.r);
      pop();

      // Advance to the next coordinate frame
      this.Index++;
    } else {
      // Optional: Reset index to 0 to loop the orbit animation when data ends
      this.Index = 0; 
    }
  }
}


let solarSystem = [];


async function setup() {
  createCanvas(800, 600, WEBGL);

  solarSystem.push(new Planet('./assets/cuerpo_1.txt', 50, color(255, 251, 0)));
  solarSystem.push(new Planet('./assets/cuerpo_2.txt', 50, color(56, 113, 240)));
  solarSystem.push(new Planet('./assets/cuerpo_3.txt', 50, color(245, 99, 50)));

  // Automatically trigger file loading for every planet in the array
  for (let planet of solarSystem) {
    planet.raw_text = await loadStrings(planet.file_name);
  }
  
  // Automatically parse data for every planet in the array
  for (let planet of solarSystem) {
    planet.parseData();
  }
	//   const fruits = ["Apple", "Banana", "Cherry"]; 
	// console.log( fruits);
  for (let planet of solarSystem) {

	  console.log(planet.file_name)
	  console.log(planet.raw_text)
  }
}

function draw() {
  background(10);
  orbitControl(); // Camera control
  
  // Lighting setup
  ambientLight(80);
  pointLight(255, 255, 255, 0, 0, 0);

  // Tell every planet to calculate its next position and draw its sphere
  for (let planet of solarSystem) {
    planet.display();
  }
}

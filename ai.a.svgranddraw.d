// I used the information from the web search results to help me write the code
import std.stdio;
import std.random;
import std.conv;
import std.string;

// A function that generates a random color in hexadecimal format
string randomColor() {
    return "#" ~ toHexString(uniform(0, 16777215));
}

// A function that generates a random SVG element with a given tag and attributes
string randomSVGElement(string tag, string[string] attrs) {
    string element = "<" ~ tag;
    foreach (key, value; attrs) {
        element ~= " " ~ key ~ "=\"" ~ value ~ "\"";
    }
    element ~= "/>";
    return element;
}

// A function that generates a random SVG animation element with a given type and attributes
string randomSVGAnimationElement(string type, string[string] attrs) {
    string element = "<animateTransform attributeName=\"transform\" type=\"" ~ type ~ "\"";
    foreach (key, value; attrs) {
        element ~= " " ~ key ~ "=\"" ~ value ~ "\"";
    }
    element ~= "/>";
    return element;
}

// A function that generates a random SVG shape with a given tag and size
string randomSVGShape(string tag, int size) {
    string shape = "";
    string color = randomColor();
    switch (tag) {
        case "circle":
            shape = randomSVGElement(tag, [
                "cx": to!string(uniform(0, size)),
                "cy": to!string(uniform(0, size)),
                "r": to!string(uniform(0, size / 2)),
                "fill": color
            ]);
            break;
        case "rect":
            shape = randomSVGElement(tag, [
                "x": to!string(uniform(0, size)),
                "y": to!string(uniform(0, size)),
                "width": to!string(uniform(0, size)),
                "height": to!string(uniform(0, size)),
                "fill": color
            ]);
            break;
        case "ellipse":
            shape = randomSVGElement(tag, [
                "cx": to!string(uniform(0, size)),
                "cy": to!string(uniform(0, size)),
                "rx": to!string(uniform(0, size / 2)),
                "ry": to!string(uniform(0, size / 2)),
                "fill": color
            ]);
            break;
        case "polygon":
            int n = uniform(3, 10); // number of points
            string points = "";
            for (int i = 0; i < n; i++) {
                points ~= to!string(uniform(0, size)) ~ "," ~ to!string(uniform(0, size)) ~ " ";
            }
            shape = randomSVGElement(tag, [
                "points": points,
                "fill": color
            ]);
            break;
        default:
            break;
    }
    return shape;
}

// A function that generates a random SVG animation with a given type and duration
string randomSVGAnimation(string type, int duration) {
    string animation = "";
    switch (type) {
        case "rotate":
            animation = randomSVGAnimationElement(type, [
                "from": to!string(uniform(0, 360)),
                "to": to!string(uniform(0, 360)),
                "dur": to!string(duration) ~ "s",
                "repeatCount": "indefinite"
            ]);
            break;
        case "scale":
            animation = randomSVGAnimationElement(type, [
                "from": to!string(uniform(0.1, 2.0)),
                "to": to!string(uniform(0.1, 2.0)),
                "dur": to!string(duration) ~ "s",
                "repeatCount": "indefinite"
            ]);
            break;
        case "translate":
            animation = randomSVGAnimationElement(type, [
                "from": to!string(uniform(-100, 100)) ~ " " ~ to!string(uniform(-100, 100)),
                "to": to!string(uniform(-100, 100)) ~ " " ~ to!string(uniform(-100, 100)),
                "dur": to!string(duration) ~ "s",
                "repeatCount": "indefinite"
            ]);
            break;
        case "skewX":
            animation = randomSVGAnimationElement(type, [
                "from": to!string(uniform(-45, 45)),
                "to": to!string(uniform(-45, 45)),
                "dur": to!string(duration) ~ "s",
                "repeatCount": "indefinite"
            ]);
            break;
        case "skewY":
            animation = randomSVGAnimationElement(type, [
                "from": to!string(uniform(-45, 45)),
                "to": to!string(uniform(-45, 45)),
                "dur": to!string(duration) ~ "s",
                "repeatCount": "indefinite"
            ]);
            break;
        default:
            break;
    }
    return animation;
}

// A function that generates a random SVG with a given size and number of shapes
string randomSVG(int size, int numShapes) {
    string svg = "<svg width=\"" ~ to!string(size) ~ "\" height=\"" ~ to!string(size) ~ "\" xmlns=\"http://www.w3.org/2000/svg\">";
    string[] tags = ["circle", "rect", "ellipse", "polygon"];
    for (int i = 0; i < numShapes; i++) {
        string tag = tags[uniform(0, tags.length)];
        string shape = randomSVGShape(tag, size);
        string animation = randomSVGAnimation(tag, uniform(1, 10));
        svg ~= shape ~ animation;
    }
    svg ~= "</svg>";
    return svg;
}

// A function that generates a random HTML with a given SVG
string randomHTML(string svg) {
    string html = "<!DOCTYPE html><html><head><style>body { margin: 0; }</style></head><body>";
    html ~= svg;
    html ~= "</body></html>";
    return html;
}

// A function that writes a string to a file
void writeToFile(string filename, string content) {
    auto file = File(filename, "w");
    file.write(content);
    file.close();
}

void main() {
    // Generate a random SVG with a size of 500 and 10 shapes
    string svg = randomSVG(500, 10);

    // Generate a random HTML with the SVG
    string html = randomHTML(svg);

    // Write the HTML to a file
    writeToFile("randomSVG.html", html);

    // Print a message
    writeln("The program has generated a randomSVG.html file.");
}

// Include the D3.js library
<script src="https://d3js.org/d3.v5.min.js"></script>

<script>
// Create an SVG container
var svgContainer = d3.select("body").append("svg")
                                    .attr("width", 200)
                                    .attr("height", 200);

// Draw a circle
var circle = svgContainer.append("circle")
                         .attr("cx", 30)
                         .attr("cy", 30)
                         .attr("r", 20);

// Add animation
circle.transition()
      .duration(1000)
      .attr("cx", 100)
      .attr("cy", 100);

// Change color over time
circle.transition()
      .duration(2000)
      .style("fill", "purple");
</script>

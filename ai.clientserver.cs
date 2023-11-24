using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;

[ApiController]
[Route("api/[controller]")]
public class MethodController : ControllerBase
{
    private readonly ILogger<MethodController> _logger;

    public MethodController(ILogger<MethodController> logger)
    {
        _logger = logger;
    }

    [HttpGet]
    public ActionResult Get()
    {
        // Execute the method here and return the result.
        return Ok("Method executed successfully.");
    }
}

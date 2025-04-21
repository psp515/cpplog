using Microsoft.AspNetCore.Identity.Data;
using System.Text.Json;

namespace LogHttpServer.Logging;

public static class AddLogsEndpoint
{
    public static IEndpointRouteBuilder AddLogsEndpoints(this IEndpointRouteBuilder builder)
    {
        builder.MapPost("/logs/single", AddLog)
            .WithName("Create Log")
            .WithOpenApi();
        return builder;
    }

    public static async Task<IResult> AddLog(LogRequest request, ILogger<LogRequest> logger)
    {
        if (request.Message.Length == 0)
        {
            logger.LogError("Log message is not valid");
            return Results.BadRequest("No log provided");
        }

        // Simulate processing
        await Task.Delay(500);

        var timestamp = DateTime.UtcNow.ToString("yyyy-MM-dd HH:mm:ss");

        var logMessage = $"[{timestamp}] Received log message: {JsonSerializer.Serialize(request)}";

        logger.LogInformation(logMessage);

        return Results.NoContent();
    }
}

using System.Text.Json;

namespace LogHttpServer.Logging;

public static class AddLogsEndpoint
{
    public static IEndpointRouteBuilder AddLogsEndpoints(this IEndpointRouteBuilder builder)
    {
        builder.MapPost("/logs", AddLogs)
            .WithName("Create Logs")
            .WithOpenApi();

        builder.MapPost("/logs/single", AddLog)
            .WithName("Create Log")
            .WithOpenApi();

        return builder;
    }

    public static async Task<IResult> AddLogs(LogsRequest request, ILogger<LogsRequest> logger)
    {
        if (request.Logs.Count == 0)
        {
            logger.LogError("Logs file is not valid");
            return Results.BadRequest("No logs provided");
        }

        await Task.Delay(2000);

        logger.LogInformation("Received ({count}) messages:", request.Logs.Count);

        foreach (var log in request.Logs)
        {
            logger.LogInformation("Received log message: {message}", JsonSerializer.Serialize(request));
        }

        return Results.NoContent();
    }

    public static async Task<IResult> AddLog(LogRequest request, ILogger<LogsRequest> logger)
    {
        if (request.Message.Length == 0)
        {
            logger.LogError("Log message is not valid");
            return Results.BadRequest("No log provided");
        }

        await Task.Delay(2000);

        logger.LogInformation("Received log message: {message}", JsonSerializer.Serialize(request));
        
        return Results.NoContent();
    }
}

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

        logger.LogInformation("Received ({count}) messages:", request.Logs);

        foreach (var log in request.Logs)
        {
            logger.LogInformation("Message: {message}", log.Message);
        }

        return Results.Ok();
    }

    public static async Task<IResult> AddLog(LogRequest request, ILogger<LogsRequest> logger)
    {
        await Task.Delay(2000);

        logger.LogInformation("Received log message: {message}", request.Message);
        
        return Results.Ok();
    }
}

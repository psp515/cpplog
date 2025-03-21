namespace LogHttpServer.Logging;

public class LogsRequest
{
    public record LogDto
    {
        public string Message { get; set; } = string.Empty;
    }

    public List<LogDto> Logs { get; set; } = [];
}

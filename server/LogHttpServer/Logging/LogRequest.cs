using System.Text.Json.Serialization;

namespace LogHttpServer.Logging;

public class LogRequest
{
    public string Message { get; set; } = string.Empty;

    public string Time { get; set; } = string.Empty;

    public string Level { get; set; } = string.Empty;

    public int? Thread { get; set; }

    [JsonPropertyName("source_file")]
    public string SourceFile { get; set; } = string.Empty;

    [JsonPropertyName("source_function")]
    public string SourceFunction { get; set; } = string.Empty;
}

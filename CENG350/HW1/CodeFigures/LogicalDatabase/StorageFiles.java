import java.util.Date;

/**
 * Represents physical media files stored in cold or hot storage.
 */
public class StorageFile {

    // Attributes
    public String file_id;
    public String filename;
    public String storage_type; // Enum: "Cold" | "Hot"
    public double file_size;
    public Date last_accessed;
    public String transfer_status; // "Pending", "Transferred"

    // Relationships
    public Movie movie; // 1 (Each storage file corresponds to one movie)

    // Constructor
    public StorageFile() {}
}

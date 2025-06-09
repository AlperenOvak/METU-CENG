import java.util.Date;
import java.util.List;

/**
 * Represents a video file in the system.
 */
public class Movie {

    // Attributes
    public String movie_id;
    public String filename;
    public double duration;
    public String format;
    public String storage_location;
    public Date date_uploaded;

    // Relationships
    public Site site; // 1 (Each movie is recorded at exactly one site)
    public List<Subject> subjects; // 0..* (A movie may have multiple subjects/clips)
    public StorageFile storageFile; // 1 (Each movie has one storage file)

    // Constructor
    public Movie() {}
}

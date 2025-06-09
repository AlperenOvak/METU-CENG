import java.util.List;

/**
 * Represents a video clip or image frame in the system.
 */
public class Subject {

    // Attributes
    public String subject_id;
    public String movie_id; // Foreign Key to Movie
    public int frame_number; // If it's an image
    public double clip_start_time; // If it's a video
    public double clip_end_time; // If it's a video

    // Relationships
    public List<Annotation> annotations; // 0..* (A subject may have multiple annotations)
    public List<ModelAnnotation> modelAnnotations; // 0..* (A subject may have multiple AI classifications)

    // Constructor
    public Subject() {}
}

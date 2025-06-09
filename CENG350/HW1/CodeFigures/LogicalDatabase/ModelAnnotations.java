import java.util.Date;

/**
 * Represents an AI-generated classification result.
 */
public class ModelAnnotation {

    // Attributes
    public String model_annotation_id;
    public String model_id;
    public Subject subject; // 1 (Each AI classification is linked to one subject)
    public double confidence;
    public String bounding_box; // JSON representation of bounding box
    public Date created_on;

    // Constructor
    public ModelAnnotation() {}
}

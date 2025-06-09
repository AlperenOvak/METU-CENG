
import java.io.*;
import java.util.*;

/**
 * 
 */
public class Database Services extends User Interface {

    /**
     * Default constructor
     */
    public Database Services() {
    }

    /**
     * 
     */
    public String database_id;

    /**
     * 
     */
    public String annot_id;

    /**
     * 
     */
    public String metadata_id;

    /**
     * 
     */
    public String user_id;

    /**
     * @param annot_id 
     * @param media_id 
     * @param user_id 
     * @param species 
     * @return
     */
    public Boolean store_anno_data(String annot_id, String media_id, String user_id, String species) {
        // TODO implement here
        return null;
    }

    /**
     * @param media_id 
     * @return
     */
    public JSON retrieve_annotation_data(String media_id) {
        // TODO implement here
        return null;
    }

    /**
     * @param annot_id 
     * @return
     */
    public Boolean delete_annotation_data(String annot_id) {
        // TODO implement here
        return null;
    }

    /**
     * @param media_id 
     * @param classification_result 
     * @return
     */
    public Boolean store_model_results(String media_id, JSON classification_result) {
        // TODO implement here
        return null;
    }

    /**
     * @param media_id 
     * @return
     */
    public JSON retrieve_model_results(String media_id) {
        // TODO implement here
        return null;
    }

}
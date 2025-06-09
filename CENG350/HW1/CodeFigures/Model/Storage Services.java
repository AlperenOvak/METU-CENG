
import java.io.*;
import java.util.*;

/**
 * 
 */
public class Storage Services extends User Interface {

    /**
     * Default constructor
     */
    public Storage Services() {
    }

    /**
     * 
     */
    public String storage_id;

    /**
     * 
     */
    public String storage_path;

    /**
     * 
     */
    public Enum mp4 mov jpg file_type;

    /**
     * 
     */
    public Enum Cold Hot storage_type;

    /**
     * @param file 
     * @param metadata 
     * @param storage_type 
     * @return
     */
    public Boolean store_file(Binary file, JSON metadata, Enum storage_type) {
        // TODO implement here
        return null;
    }

    /**
     * @param file_id 
     * @return
     */
    public Binary retrieve_file(String file_id) {
        // TODO implement here
        return null;
    }

    /**
     * @param file_id 
     * @return
     */
    public Boolean delete_file(String file_id) {
        // TODO implement here
        return null;
    }

    /**
     * @param file_id 
     * @return
     */
    public Boolean transfer_to_hot_storage(String file_id) {
        // TODO implement here
        return null;
    }

    /**
     * @param file_id 
     * @return
     */
    public Boolean transfer_to_cold_storage(String file_id) {
        // TODO implement here
        return null;
    }

}
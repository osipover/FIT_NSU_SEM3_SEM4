package factory.factory_config;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class FactoryConfig {
    private static int warehouseBodySize;
    private static int warehouseEngineSize;
    private static int warehouseAccessorySize;
    private static int warehouseCarSize;
    private static int numOfAccessorySuppliers;
    private static int numOfDealers;
    private static int numOfWorkers;

    public static void init() {
        Properties prop = new Properties();
        try (InputStream inputStream = FactoryConfig.class.getResourceAsStream("/factory_config/factoryconf.properties")) {
            prop.load(inputStream);
            warehouseBodySize       = Integer.parseInt(prop.getProperty("warehouseBodySize"));
            warehouseEngineSize     = Integer.parseInt(prop.getProperty("warehouseEngineSize"));
            warehouseAccessorySize  = Integer.parseInt(prop.getProperty("warehouseAccessorySize"));
            warehouseCarSize        = Integer.parseInt(prop.getProperty("warehouseCarSize"));
            numOfAccessorySuppliers = Integer.parseInt(prop.getProperty("numOfAccessorySuppliers"));
            numOfDealers            = Integer.parseInt(prop.getProperty("numOfDealers"));
            numOfWorkers            = Integer.parseInt(prop.getProperty("numOfWorkers"));
        } catch (IOException ex) {}
    }

    public static int getWarehouseBodySize() {
        return warehouseBodySize;
    }

    public static int getWarehouseEngineSize() {
        return warehouseEngineSize;
    }

    public static int getWarehouseAccessorySize() {
        return warehouseAccessorySize;
    }

    public static int getWarehouseCarSize() {
        return warehouseCarSize;
    }

    public static int getNumOfAccessorySuppliers() {
        return numOfAccessorySuppliers;
    }

    public static int getNumOfDealers() {
        return numOfDealers;
    }

    public static int getNumOfWorkers() {
        return numOfWorkers;
    }
}

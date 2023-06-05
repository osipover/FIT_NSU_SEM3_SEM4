package GUI.components;

import observer.Observer;

import javax.swing.*;
import java.awt.*;

public class ProductInfoPanel extends JPanel implements Observer {
    private JLabel totalProductsLabel = new JLabel();
    private JLabel currentNumProductsLabel = new JLabel();

    public ProductInfoPanel() {
        initTotalProductsLabel();
        initCurrentNumProductsLabel();
        initPanel();
    }

    void initPanel() {
        GridBagLayout gridBagLayout = new GridBagLayout();
        setLayout(gridBagLayout);

        GridBagConstraints constraints = new GridBagConstraints();
        constraints.weightx = 0;
        constraints.weighty = 0;

        constraints.fill = GridBagConstraints.HORIZONTAL;
        constraints.gridy = 0;
        add(totalProductsLabel, constraints);

        constraints.fill = GridBagConstraints.HORIZONTAL;
        constraints.gridy = 2;
        add(currentNumProductsLabel, constraints);
    }

    void initTotalProductsLabel() {
        totalProductsLabel.setText("Total products: " + 0);
        totalProductsLabel.setSize(new Dimension(300, 200));
    }

    void initCurrentNumProductsLabel() {
        currentNumProductsLabel.setText("Current products: " + 0);
        currentNumProductsLabel.setSize(new Dimension(300, 200));
    }

    @Override
    public void update(int totalProducts, int currentNumProducts) {
        totalProductsLabel.setText("Total products: " + totalProducts);
        currentNumProductsLabel.setText("Current products: " + currentNumProducts);
    }
}

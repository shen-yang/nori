frequencies = [ 0, 1, 1, 1, 5, 64, 336, 861, 869, 305, 39, 5, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 12, 655, 21277, 138268, 127143, 16687, 384, 4, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 117, 21738, 325812, 290028, 15223, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 402, 21295, 18179, 214, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 9, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ];
expFrequencies = [ 0.0357822, 0.0724529, 0.234182, 1.52411, 17.7806, 200.023, 1250.8, 3243.32, 3107.02, 1104.83, 165.663, 14.3148, 1.26301, 0.206864, 0.0672276, 0.0342206, 0.0232164, 0.0194735, 0.0196224, 0.023781; 6.78301e-007, 2.85104e-005, 0.00220455, 0.225139, 23.8563, 2050.89, 70789.8, 452831, 416773, 55543.9, 1436.52, 16.1037, 0.151415, 0.00150137, 2.01715e-005, 5.1371e-007, 3.51184e-008, 8.67623e-009, 9.24303e-009, 4.21045e-008; 4.8131e-017, 2.25586e-013, 2.52033e-009, 3.27675e-005, 0.212283, 331.304, 67299.1, 978661, 870886, 47138.4, 190.479, 0.105536, 1.48958e-005, 1.12165e-009, 1.05943e-013, 2.27425e-017, 0, 0, 0, 0; 0, 0, 0, 8.88817e-014, 5.87047e-007, 0.196224, 1091.59, 56263.9, 47986.2, 628.007, 0.0771347, 1.70665e-007, 2.13411e-014, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 1.18815e-008, 0.0455648, 25.6999, 20.6286, 0.0176956, 2.2318e-009, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 1.16465e-010, 1.31156e-005, 9.57352e-006, 1.82684e-011, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 1.77907e-016, 1.04583e-016, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ];
colormap(jet);
clf; subplot(2,1,1);
imagesc(frequencies);
title('Observed frequencies');
axis equal;
subplot(2,1,2);
imagesc(expFrequencies);
axis equal;
title('Expected frequencies');
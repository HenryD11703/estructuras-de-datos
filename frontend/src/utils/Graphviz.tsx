import React, { useEffect, useState } from 'react';
import Viz from 'viz.js';
import { Module, render } from 'viz.js/full.render.js';
import styles from './Graphviz.module.css';

interface GraphvizComponentProps {
  input?: string;
}

const GraphvizComponent: React.FC<GraphvizComponentProps> = ({ input }) => {
  const defaultGraph: string = `digraph G {
    E -> R
    r -> o
    o -> R
  }`;

  const [svg, setSvg] = useState<string>(defaultGraph);

  useEffect(() => {
    const graphToRender = input || defaultGraph;
    const viz = new Viz({ Module, render });
    viz
      .renderString(graphToRender)
      .then((result) => {
        // Modificar el SVG para agregar un viewBox si no lo tiene
        if (!result.includes('viewBox')) {
          const modifiedResult = result.replace(
            /<svg/,
            '<svg viewBox="0 0 1000 1000"'
          );
          setSvg(modifiedResult);
        } else {
          setSvg(result);
        }
      })
      .catch((error) => console.error(error));
  }, [input, defaultGraph]);

  return (
    <div className={styles.graphvizWrapper}>
      <div className={styles.graphvizScroll}>
        <div className={styles.graphvizContainer}>
          <div dangerouslySetInnerHTML={{ __html: svg }} />
        </div>
      </div>
    </div>
  );
};

export default GraphvizComponent;

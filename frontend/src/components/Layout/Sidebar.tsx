import styles from './Sidebar.module.css';
import { ImDatabase } from 'react-icons/im';
import { MdChevronLeft, MdChevronRight } from 'react-icons/md';
import { useState } from 'react';

interface SidebarProps {
  onSelectStructure: (structure: string) => void;
}

const Sidebar = ({ onSelectStructure }: SidebarProps) => {
  const structures = [
    { name: 'Linked List', icon: '📃' },
    { name: 'Doubly Linked List', icon: '📜' },
    { name: 'Doubly Circular Linked List', icon: '🔄' },
    { name: 'Binary Search Tree (BST)', icon: '🌳' },
    { name: 'AVL Tree', icon: '🏗️' },
    { name: 'Red-Black Tree', icon: '🍁' },
    { name: 'B-Tree', icon: '🌴' },
  ];

  const [activeIndex, setActiveIndex] = useState<number | null>(null);
  const [isCollapsed, setIsCollapsed] = useState(false);

  const handleSelect = (name: string, index: number) => {
    onSelectStructure(name);
    setActiveIndex(index);
  };

  const toggleSidebar = () => {
    setIsCollapsed(!isCollapsed);
  };

  return (
    <div className={`${styles.Sidebar} ${isCollapsed ? styles.Collapsed : ''}`}>
      <div className={styles.Header}>
        <ImDatabase className={styles.HeaderIcon} />
        {!isCollapsed && <h2 className={styles.Title}>Data Structures</h2>}
      </div>
      <button className={styles.ToggleButton} onClick={toggleSidebar}>
        {isCollapsed ? (
          <MdChevronRight size={20} />
        ) : (
          <MdChevronLeft size={20} />
        )}
      </button>
      <ul className={styles.StructureList}>
        {structures.map((structure, index) => (
          <li
            key={index}
            className={`${styles.Item} ${activeIndex === index ? styles.Active : ''}`}
            onClick={() => handleSelect(structure.name, index)}
            title={isCollapsed ? structure.name : ''}
          >
            <span className={styles.Icon}>{structure.icon}</span>
            {!isCollapsed && structure.name}
          </li>
        ))}
      </ul>
    </div>
  );
};

export default Sidebar;
